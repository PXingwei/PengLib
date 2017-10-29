#ifndef _DUALCIRCLELIST_H__
#define _DUALCIRCLELIST_H__
#include "DualLinkList.h"
#include "LinuxList.h"

namespace PengLib
{
	template <typename T>
	class DualCircleList : public DualLinkList<T>
	{
	protected:
		struct Node : public Object
		{
			list_head head;
			T value;
		};

		list_head m_header;
		list_head* m_current;

		list_head* position(int i) const
		{
			list_head* ret = const_cast<list_head*>(&m_header);

			for(int p=0; p<i; p++)
			{
				ret = ret->next;
			}

			return ret;
		}

		int mod(int i) const
		{
			return (this->m_length == 0 ? 0 : i % this->m_length);
		}

	public:

		DualCircleList()
		{
			this->m_length = 0;
			this->m_step = 0;
			m_current = NULL;
			INIT_LIST_HEAD(&m_header);
		}

		bool insert(const T& e)
		{
			return insert(this->m_length, e);
		}

		bool insert(int i, const T& e)
		{
			bool ret = true;

			i = i % (this->m_length + 1);

			if(ret)
			{
				Node* node = new Node();

				if(node != NULL)
				{
					node->value = e;
					list_add_tail(&(node->head), position(i)->next);
					this->m_length++;
				}
				else
				{
                    THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory to insert a new object");
				}
			}

			return ret;
		}

		bool remove(int i)
        {
        	bool ret = true;

        	i = mod(i);
        	ret = (0 <= i) && (i < this->m_length);

        	if(ret)
        	{
        		list_head* toDel = position(i)->next;

        		if(m_current == toDel)
        		{
        			m_current = m_current->next;
        		}

        		list_del(toDel);

        		delete list_entry(toDel, Node, head);
        		this->m_length--;
        	}

        	return ret;
        }

        T get(int i) const
        {

        	T ret;
        	i = mod(i);

			if( get(i, ret) )
            {

                return ret;
            }
            else
            {

                THROW_EXCEPTION(indexOutOfBoundsException, "Invalid input parameter");
            }
        }

        bool get(int i, T& e) const
        {
            i = mod(i);
            bool ret = (0 <= i) && (i < this->m_length);

            if(ret)
            {

                list_head* current = position(i)->next;

                e = list_entry(current, Node, head)->value;
            }

            return ret;
        }

        bool set(int i, const T& e)
        {
        	i = mod(i);
            bool ret = (0 <= i) && (i < this->m_length);

            if(ret)
            {

                list_head* current = position(i)->next;

                list_entry(current, Node, head)->value = e;
            }

            return ret;
        }

        int find(const T& e) const
        {

            int ret = -1;
            int i = 0;
            list_head* node = NULL;

            list_for_each(node, &m_header)
            {

                if(list_entry(node, Node, head)->value == e)
                {
                    ret = i;
                    break;
                }
                i++;
            }

            return ret;
        }

        T& current()
        {
            if(!end())
            {
                return list_entry(m_current, Node, head)->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No value at current position");
            }
        }

        bool move(int i, int step = 1)
        {
        	i = mod(i);

            bool ret = (0 <= i) && (i < this->m_length) && (step > 0);

            if(ret)
            {

                m_current = position(i)->next;
                this->m_step = step;
            }

            return ret;
        }

        bool end()
        {
            return ((m_current == NULL) || (this->m_length == 0));
        }


        bool next()
        {

            int i=0;

            while(!end() && (i<this->m_step))
            {
            	if(m_current == &m_header)
            	{
            		m_current = m_current->next;
            	}
            	else
            	{
            		i++;
                	m_current = m_current->next;
            	}             
            }

            if(m_current == &m_header)
            {
            	m_current = m_current->next;
            }

            return (i == this->m_step);
        }

        bool prev()
        {

            int i=0;

            while(!end() && (i<this->m_step))
            {

                if(m_current == &m_header)
            	{
            		m_current = m_current->prev;
            	}
            	else
            	{
            		i++;
                	m_current = m_current->prev;
            	}     
            }

            if(m_current == &m_header)
            {
            	m_current = m_current->prev;
            }

            return (i == this->m_step);
        }

        void clear()
        {
            while(this->m_length>0)
        	{
        		remove(0);
        	}
        }

        ~DualCircleList()
        {
        	clear();
        }

	};
}

#endif
