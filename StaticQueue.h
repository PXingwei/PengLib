#ifndef _STATICQUEUE_H__
#define _STATICQUEUE_H__
#include "Queue.h"
#include "Exception.h"

namespace PengLib
{
	template <typename T, int N>
    class StaticQueue : public Queue<T>
	{
	protected:
        int m_front;
		int m_rear;
		int m_size;
		T m_space[N];

	public:

		StaticQueue()
		{
			m_front = 0;
			m_rear = 0;
			m_size = 0;
		}

		void add(const T& e)
		{
			if(m_size+1 <= N)
			{
				m_space[m_rear] = e;
				m_rear = (m_rear + 1) % N;
				m_size++;
			}
			else
			{
                THROW_EXCEPTION(InvalidOperationException, "No space in the queue to add an element");
			}
		}

		void remove()
		{
			if(m_size >0)
			{
				m_front = (m_front + 1) % N;
				m_size--;
			}
			else
			{
                THROW_EXCEPTION(InvalidOperationException, "There is no element in the queue");
			}
		}

		int size() const
		{
			return m_size;
		}

		void clear()
		{
			m_front = 0;
			m_rear = 0;
			m_size = 0;			
		}

		T front() const
		{
			if(m_size >0)
			{
				return m_space[m_front];
			}
			else
			{
                THROW_EXCEPTION(InvalidOperationException, "There is no element in the queue");
			}
		}

		~StaticQueue()
		{
			clear();
		}
	};
}

#endif
