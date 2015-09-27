#include "gc.h"

namespace elsa {
	namespace vm {

		GC::GC()
			:
			num_marked_(0),
			num_swept_(0),
			heap_(nullptr)
		{}

		GC::GC(Heap* heap)
			:
			num_marked_(0),
			num_swept_(0),
			heap_(heap)
		{}

		GCResult GC::collect(StackFrame* top_frame)
		{
			if (heap_ == nullptr)
				throw RuntimeException("The GC must have a pointer to the VM's heap object");

			num_marked_ = 0;
			num_swept_ = 0;

			markAll(top_frame);
			sweep();

			return GCResult(num_marked_, num_swept_);
		}

		void GC::markAll(StackFrame* top_frame)
		{
			auto current_frame = top_frame;
			while (current_frame != nullptr)
			{
				for (std::size_t li = 0; li < current_frame->locals_size_; ++li)
				{
					mark(current_frame->locals_[li]);
				}

				for (std::vector<Object>::size_type vi = 0; vi != current_frame->eval_stack_.size(); ++vi)
				{
					mark(current_frame->eval_stack_.at(vi));
				}

				for (auto& obj : current_frame->eval_stack_)
				{
					mark(obj);
				}

				current_frame = current_frame->get_parent();
			}
		}

		void GC::sweep()
		{
			
		}

		void GC::mark(Object& obj)
		{
			if (obj.get_type() != OType::GCOPtr)
				return;

			auto gco = obj.gco();
			if (gco->marked)
				return;

			gco->marked = true;
			num_marked_++;

			if (gco->type == GCObjectType::Array)
				mark_array(obj);
			else if (gco->type == GCObjectType::Struct)
				mark_struct(obj);
			else
				throw RuntimeException("Invalid GCObjectType.");
		}

		void GC::mark_struct(Object& obj)
		{
			auto gco = obj.gco();
			for (auto& field : gco->si->get_fields())
			{
				if (field->get_type() != OType::GCOPtr)
					continue;

				auto field_obj = heap_->load_field(obj, field.get());

				if (field_obj.gco() == nullptr)
					continue;

				mark(field_obj);
			}
		}

		void GC::mark_array(Object& obj)
		{

		}
	}
}

