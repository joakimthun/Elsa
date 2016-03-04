#include "native_calls.h"

#include "windows/window.h"
#include "file_handle.h"

namespace elsa {
	namespace vm {

		static LARGE_INTEGER frequency;
		static LARGE_INTEGER start_time;

		NativeCalls::NativeCalls()
		{
			initialize();
			if (!QueryPerformanceFrequency(&frequency))
				throw RuntimeException("NativeCalls::get_time: Call to QueryPerformanceFrequency failed");

			QueryPerformanceCounter(&start_time);
		}
		
		void NativeCalls::invoke(std::size_t index, StackFrame* frame, Heap* heap)
		{
			functions_[index](frame, heap);
		}
		
		void NativeCalls::initialize()
		{
			functions_.push_back(print);
			functions_.push_back(print_ln);
			functions_.push_back(are_eq);
			functions_.push_back(assert_eq);
			functions_.push_back(ref_eq);
			functions_.push_back(create_window);
			functions_.push_back(open_window);
			functions_.push_back(close_window);
			functions_.push_back(update_window);
			functions_.push_back(fill_rect);
			functions_.push_back(sleep);
			functions_.push_back(get_ticks);
			functions_.push_back(key_down);
			functions_.push_back(fill_circle);
			functions_.push_back(render_text);
			functions_.push_back(file_open);
			functions_.push_back(file_close);
			functions_.push_back(file_read);
			functions_.push_back(file_write);
			functions_.push_back(window_blt);
		}

		void NativeCalls::print(StackFrame* frame, Heap* heap)
		{
			print_internal(frame, heap);
		}

		void NativeCalls::print_ln(StackFrame* frame, Heap* heap)
		{
			print_internal(frame, heap);
			std::cout << std::endl;
		}

		void NativeCalls::print_internal(StackFrame* frame, Heap* heap)
		{
			auto object = frame->pop();

			if (is_string(object))
			{
				std::wcout << read_string(object, heap);

				return;
			}

			if (object.get_type() == elsa::VMType::Int)
				std::cout << object.i();
			else if (object.get_type() == elsa::VMType::Float)
				std::cout << object.f();
			else if (object.get_type() == elsa::VMType::Char)
				std::wcout << object.c();
			else if (object.get_type() == elsa::VMType::Byte)
				std::wcout << object.b();
			else
				throw RuntimeException("Unsupported type: print_ln");
		}

		void NativeCalls::are_eq(StackFrame* frame, Heap* heap)
		{
			frame->push(Object(are_eq_internal(frame)));
		}

		bool NativeCalls::are_eq_internal(StackFrame* frame)
		{
			const auto o1 = frame->pop();
			const auto o2 = frame->pop();

			if (o1.get_type() != o2.get_type())
				return false;

			if (o1.get_type() == VMType::GCOPtr)
			{
				return ref_eq_internal(o1, o2);
			}
			else
			{
				switch (o1.get_type())
				{
				case VMType::Int:
					return o1.i() == o2.i();
				case VMType::Float:
					return o1.f() == o2.f();
				case VMType::Char:
					return o1.c() == o2.c();
				case VMType::Byte:
					return o1.b() == o2.b();
				default:
					throw RuntimeException("Equals failed, unknown type.");
				}
			}

			return true;
		}

		void NativeCalls::assert_eq(StackFrame* frame, Heap* heap)
		{
			if (!are_eq_internal(frame))
				throw RuntimeException("AssertEq failed.");
		}

		void NativeCalls::ref_eq(StackFrame* frame, Heap* heap)
		{
			const auto first = frame->pop();
			const auto second = frame->pop();

			if(first.get_type() != VMType::GCOPtr || second.get_type() != VMType::GCOPtr)
				throw RuntimeException("Reference equals is only supported for reference types.");

			frame->push(Object(ref_eq_internal(first, second)));
		}

		bool NativeCalls::ref_eq_internal(const Object& first, const Object& second)
		{
			if (first.gco()->type != second.gco()->type)
				return false;

			if (first.gco()->type == GCObjectType::Array)
			{
				if (first.gco()->ai->type != second.gco()->ai->type)
					return false;

				if (first.gco()->ptr != second.gco()->ptr)
					return false;
			}
			else
			{
				if (first.gco()->si->get_name() != second.gco()->si->get_name())
					return false;

				if (first.gco()->ptr != second.gco()->ptr)
					return false;
			}

			return true;
		}

		void NativeCalls::create_window(StackFrame* frame, Heap* heap)
		{
			auto height = frame->pop().i();
			auto width = frame->pop().i();
			auto title = read_string(frame->pop(), heap);

			frame->push(heap->allocate_resource_handle(new Window(title, width, height)));
		}

		void NativeCalls::open_window(StackFrame* frame, Heap* heap)
		{
			auto w = get_window_handle(frame->pop());
			w->open();
		}

		void NativeCalls::close_window(StackFrame* frame, Heap* heap)
		{

		}

		void NativeCalls::update_window(StackFrame* frame, Heap* heap)
		{
			auto w = get_window_handle(frame->pop());
			w->update();
		}

		void NativeCalls::fill_rect(StackFrame * frame, Heap * heap)
		{
			auto b = frame->pop().i();
			auto g = frame->pop().i();
			auto r = frame->pop().i();
			auto height = frame->pop().i();
			auto width = frame->pop().i();
			auto y = frame->pop().i();
			auto x = frame->pop().i();
			auto w = get_window_handle(frame->pop());
			w->fill_rect(x, y, width, height, r, g, b);
		}

		void NativeCalls::fill_circle(StackFrame * frame, Heap * heap)
		{
			auto b = frame->pop().i();
			auto g = frame->pop().i();
			auto r = frame->pop().i();
			auto d = frame->pop().i();
			auto y = frame->pop().i();
			auto x = frame->pop().i();
			auto w = get_window_handle(frame->pop());
			w->fill_circle(x, y, d, r, g, b);
		}

		void NativeCalls::sleep(StackFrame* frame, Heap* heap)
		{
			auto sleep_time = frame->pop().i();
			Sleep(static_cast<DWORD>(sleep_time));
		}

		void NativeCalls::get_ticks(StackFrame* frame, Heap* heap)
		{
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);

			now.QuadPart -= start_time.QuadPart;
			now.QuadPart *= 1000;
			now.QuadPart /= frequency.QuadPart;

			frame->push(Object(static_cast<int>(now.QuadPart)));
		}

		void NativeCalls::key_down(StackFrame* frame, Heap* heap)
		{
			auto keycode = frame->pop().i();
			auto w = get_window_handle(frame->pop());
			frame->push(Object(w->key_down(static_cast<WPARAM>(keycode))));
		}

		void NativeCalls::render_text(StackFrame* frame, Heap* heap)
		{
			auto str = read_string(frame->pop(), heap);
			auto y = frame->pop().i();
			auto x = frame->pop().i();
			auto w = get_window_handle(frame->pop());
			w->render_text(x, y, str);
		}

		void NativeCalls::window_blt(StackFrame* frame, Heap* heap)
		{
			auto src_buffer = frame->pop();
			auto height = frame->pop().i();
			auto width = frame->pop().i();
			auto y = frame->pop().i();
			auto x = frame->pop().i();
			auto w = get_window_handle(frame->pop());

			if (src_buffer.gco() == nullptr || src_buffer.gco()->type != GCObjectType::Array || src_buffer.gco()->ai->type != VMType::Byte)
				throw RuntimeException("NativeCalls::window_blt invalid source buffer");

			w->blt(x, y, width, height, static_cast<uint8_t*>(src_buffer.gco()->ptr));
		}

		void NativeCalls::file_open(StackFrame* frame, Heap* heap)
		{
			auto m = frame->pop().i();
			auto path = read_string(frame->pop(), heap);
			frame->push(heap->allocate_resource_handle(new FileHandle(path, m)));
		}

		void NativeCalls::file_close(StackFrame* frame, Heap* heap)
		{
			auto fh = get_file_handle(frame->pop());
			fh->close();
		}

		void NativeCalls::file_read(StackFrame* frame, Heap* heap)
		{
			auto num_bytes = frame->pop().i();
			auto arr = frame->pop();
			auto fh = get_file_handle(frame->pop());
			auto num_read = fh->read(arr, num_bytes, heap);
			frame->push(Object(num_read));
		}

		void NativeCalls::file_write(StackFrame* frame, Heap* heap)
		{
		}

		std::wstring NativeCalls::read_string(Object& object, Heap* heap)
		{
			if (is_string(object))
			{
				auto char_arr = heap->load_field(object, static_cast<std::size_t>(0));
				return heap->load_string(char_arr);
			}
			else
			{
				throw RuntimeException("NativeCalls::read_string: Invalid string object");
			}
		}

		bool NativeCalls::is_string(Object & object)
		{
			return object.get_type() == VMType::GCOPtr && object.gco()->type == GCObjectType::Struct && object.gco()->si->get_name() == L"String";
		}

		Window* NativeCalls::get_window_handle(Object& object)
		{
			auto gco = object.gco();
			if (gco != nullptr && gco->type == GCObjectType::RHandle && gco->resource_handle_->get_type() == ResourceHandleType::Window)
			{
				return static_cast<Window*>(gco->resource_handle_);
			}
			else
			{
				throw RuntimeException("NativeCalls::get_window_handle: Invalid window handle");
			}
		}

		FileHandle* NativeCalls::get_file_handle(Object & object)
		{
			auto gco = object.gco();
			if (gco != nullptr && gco->type == GCObjectType::RHandle && gco->resource_handle_->get_type() == ResourceHandleType::File)
			{
				return static_cast<FileHandle*>(gco->resource_handle_);
			}
			else
			{
				throw RuntimeException("NativeCalls::get_file_handle: Invalid file handle");
			}
		}
	}
}
