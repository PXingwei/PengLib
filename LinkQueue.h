#ifndef _LINKQUEUE_H__
#define _LINKQUEUE_H__
#include "LinuxList.h"
#include "Queue.h"

namespace PengLib
{
    template <typename T>
    class LinkQueue : public Queue<T>
    {
    protected:
        int m_length;
        struct Node : public Object
        {
            list_head head;
            T value;
        };
        list_head m_header;

    public:
        LinkQueue()
        {
            m_length = 0;
            INIT_LIST_HEAD(&m_header);
        }

        void add(const T& e)
        {
            Node* node = new Node();

            if(node != NULL)
            {
                node->value = e;
                list_add_tail(&node->head, &m_header);
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to add an element");
            }
        }

        void remove()
        {
            if(m_length > 0)
            {
                list_head* toDel = m_header.next;
                list_del(toDel);
                delete list_entry(toDel, Node, head);
                m_length--;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "There is no element in the queue");
            }
        }

        int size() const
        {
            return m_length;
        }

        void clear()
        {
            if(m_length > 0)
            {
                remove();
            }
        }

        T front() const
        {
            if(m_length > 0)
            {
                return list_entry(m_header.next, Node, head)->value;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "There is no element in the queue");
            }
        }

        ~LinkQueue()
        {
            clear();
        }
    };
}

#endif
