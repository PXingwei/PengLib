#ifndef _STATICSTACK_H__
#define _STATICSTACK_H__
#include "Stack.h"
#include "Exception.h"

namespace PengLib {

	template <typename T, int N>
	class StaticStack : public Stack<T>
	{
	protected:
		int top;
		int size;
		T m_space[N];

	public:
		StaticStack()
		{
			top = -1;
			size = 0;
		}

		void push(const T& e) 
		{
			if(size < N)
			{
                m_space[top+1] = e;
				top++;
				size++;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no space to push an element");
			}
		}

		void pop()
		{
			if(size > 0)
			{
				size--;
				top--;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}

        T Top() const
		{
			if(size > 0)
			{
				return m_space[top];
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}

		void clear()
		{
			size = 0;
			top = -1;
		}

        int Size() const
		{
			return size;
		}

		int capacity() const
		{
			return N;
		}

		~StaticStack()
		{
			clear();
		}
	};
}

#endif
