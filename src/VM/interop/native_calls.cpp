#include "native_calls.h"

#include "windows\window.h"

namespace elsa {
	namespace vm {

		NativeCalls::NativeCalls()
		{
			initialize();
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
			frame->push(heap->allocate_resource_handle(new Window()));
		}

		void NativeCalls::open_window(StackFrame* frame, Heap* heap)
		{
			auto o = frame->pop();
			auto gco = o.gco();
			if (gco != nullptr && gco->type == GCObjectType::RHandle && gco->resource_handle_->get_type() == ResourceHandleType::Window)
			{
				auto w = static_cast<Window*>(gco->resource_handle_);
				w->Open();
				return;
			}

			throw RuntimeException("Invalid window handle passed to open window");
		}

		void NativeCalls::close_window(StackFrame* frame, Heap* heap)
		{
		}

		std::wstring NativeCalls::read_string(Object& object, Heap* heap)
		{
			std::wstring str;

			if (is_string(object))
			{
				auto char_arr = heap->load_field(object, static_cast<std::size_t>(0));
				for (auto i = 0; i < char_arr.gco()->ai->next_index; i++)
				{
					str.push_back(heap->load_element(char_arr, i).c());
				}

				return str;
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
	}
}
