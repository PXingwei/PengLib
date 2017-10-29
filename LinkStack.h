#ifndef _LINKSTACK_H__
#define _LINKSTACK_H__

#include "Stack.h"
#include "Exception.h"
#include "LinkList.h"

namespace PengLib
{
	template <typename T>
	class LinkStack : public Stack<T>
	{
	protected:
        LinkList<T> m_list;

	public:

		void push(const T& e)
		{
			m_list.insert(0, e);
		}

		void pop()
		{
			if(m_list.length() > 0)
			{
				m_list.remove(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
		}

		T Top() const
		{
			if(m_list.length() > 0)
			{
				return m_list.get(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "there are no element in the stack");
			}
			
		}

		void clear()
		{
			m_list.clear();
		}

		int Size() const
		{
			return m_list.length();
		}

		~LinkStack()
		{
			clear();
		}
		
	};
}

#endif
