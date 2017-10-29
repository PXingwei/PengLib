#ifndef _STACKTOQUEUE_H__
#define _STACKTOQUEUE_H__
#include "Queue.h"
#include "LinkStack.h"

namespace PengLib
{
	template <typename T>
    class StackToQueue : public Queue<T>
	{
	protected:
        mutable LinkStack<T> stack_in;
        mutable LinkStack<T> stack_out;

		void move() const
		{
            if(stack_out.Size() == 0)
			{
                while(stack_in.Size() > 0)
				{
                    stack_out.push(stack_in.Top());
                    stack_in.pop();
				}
			}
		}

	public:
		StackToQueue()
		{

		}

		void add(const T& e)
		{
            stack_in.push(e);
		}

		void remove()
		{
			move();

            if(stack_out.Size() > 0)
			{
                stack_out.pop();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}

        int size() const
		{
            return stack_in.Size() + stack_out.Size();
		}

		void clear()
		{
            stack_in.clear();
            stack_out.clear();
		}

		T front() const
		{
			move();

            if(stack_out.Size() > 0)
			{
                return stack_out.Top();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}


		~StackToQueue()
		{
			clear();
		}
		
	};
}

#endif
