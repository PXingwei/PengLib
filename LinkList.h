#ifndef _LINKLIST_H__
#define _LINKLIST_H__
#include "List.h"
#include "Exception.h"

namespace PengLib
{

    template <typename T>
    class LinkList : public List<T>
    {

    protected:
        struct Node : public Object
        {
            T value;
            Node* next;
        };

        mutable struct : public Object
        {
            char reserved[sizeof(T)];
            Node* next;

        } m_header;

        int m_length;
        Node* m_current;
        int m_step;

        Node* position(int i) const
        {
            Node* ret = reinterpret_cast<Node*>(&m_header);

            for(int p=0; p<i; p++)
            {

                ret = ret->next;
            }

            return ret;
        }

    public:
        LinkList()
        {

            m_header.next = NULL;
            m_current = NULL;
            m_length = 0;
            m_step = 1;
        }

        virtual bool insert(const T& e)
        {

            return insert(m_length, e);
        }

        virtual bool insert(int i, const T& e)
        {

            bool ret = (0 <= i) && (i <= m_length);

            if(ret)
            {

                Node* node = create();

                if(node != NULL)
                {

                Node* current = position(i);
                node->next = current->next;
                node->value = e;
                current->next = node;

                m_length++;
                }
                else
                {

                    THROW_EXCEPTION(NoEnoughMemoryException, "No Enough Memory to insert a Node Object");
                }
            }

            return ret;
        }

        virtual T& current()
        {
            if(!end())
            {

                return m_current->value;
            }
            else
            {

                THROW_EXCEPTION(InvalidOperationException, "No value at current position");
            }
        }

        virtual bool move(int i, int step = 1)
        {
            bool ret = (0 <= i) && (i < m_length) && (step > 0);

            if(ret)
            {

                m_current = position(i)->next;
                m_step = step;
            }

            return ret;
        }

        virtual bool end()
        {

            return (m_current == NULL);
        }

        virtual bool next()
        {

            int i=0;

            while(!end() && (i<m_step))
            {

                i++;
                m_current = m_current->next;
            }

            return (i == m_step);
        }

        virtual bool remove(int i)
        {

            bool ret = (0 <= i) && (i < m_length);

            if(ret)
            {

                Node* current = position(i);
                Node* toDel = current->next;

                if(m_current == toDel)
                {
                    m_current = m_current->next;
                }

                current->next = toDel->next;

                m_length--;
                destroy(toDel);
            }

            return ret;
        }

        virtual T get(int i) const
        {

            T ret;

            if( get(i, ret) )
            {

                return ret;
            }
            else
            {

                THROW_EXCEPTION(indexOutOfBoundsException, "Invalid input parameter");
            }
        }

        virtual bool get(int i, T& e) const
        {
            bool ret = (0 <= i) && (i < m_length);

            if(ret)
            {

                Node* current = position(i)->next;

                e = current->value;
            }

            return ret;
        }

        virtual bool set(int i, const T& e)
        {

            bool ret = (0 <= i) && (i < m_length);

            if(ret)
            {

                Node* current = position(i)->next;

                current->value = e;
            }

            return ret;
        }

        virtual int find(const T& e) const
        {

            int ret = -1;
            Node* node = m_header.next;
            int i= 0;

            while(node != NULL)
            {

                if(node->value == e)
                {

                    ret = i;
                    break;
                }
                else
                {

                    i++;
                    node = node->next;
                }
            }

            return ret;
        }

        virtual int length() const
        {

            return m_length;
        }

        virtual Node* create()
        {
            return new Node();
        }

        virtual void destroy(Node* pn)
        {
            delete pn;
        }

        virtual void clear()
        {

            while(m_header.next != NULL)
            {

                Node* toDel = m_header.next;
                m_header.next = toDel->next;
                m_length--;
                delete toDel;
            }

//            m_length = 0;
        }

        ~LinkList()
        {

            clear();
        }
    };

}

#endif
