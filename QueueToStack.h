#ifndef _QUEUETOSTACK_H__
#define _QUEUETOSTACK_H__
#include "Stack.h"
#include "LinkQueue.h"

namespace PengLib
{
	template <typename T>
    class QueueToStack : public Stack<T>
	{
	protected:
        LinkQueue<T>* queue_in;
        LinkQueue<T>* queue_out;
        LinkQueue<T> queue_1;
        LinkQueue<T> queue_2;

        void move() const
		{
			int length = queue_in->size() - 1;

			for (int i = 0; i < length; i++)
			{
				queue_out->add(queue_in->front());
				queue_in->remove();
			}
		}

		void swap()
		{
			LinkQueue<T>* temp = NULL;
			temp = queue_in;
			queue_in = queue_out;
			queue_out = temp;
		}

	public:
		QueueToStack()
		{
			queue_in = &queue_1;
			queue_out = &queue_2;
		}

		void push(const T& e)
		{
			queue_in->add(e);
		}

        void pop()
		{
			if(queue_in->size() > 0)
			{
				move();
				queue_in->remove();
				swap();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}

        T Top() const
        {
        	if(queue_in->size() > 0)
        	{
        		move();
				return queue_in->front();
        	}
        	else
        	{
                THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
        	}
        }

		void clear()
		{
			queue_in->clear();
			queue_out->clear();
		}

        int Size() const
        {
            return queue_in->size() + queue_out->size();
        }

		~QueueToStack()
		{
			clear();
		}
	};
}

#endif
