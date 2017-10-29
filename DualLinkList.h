#ifndef _DUALLINKLIST_H__
#define _DUALLINKLIST_H__
#include "List.h"
#include "Exception.h"

namespace PengLib {

    template <typename T>
    class DualLinkList : public List<T>
    {
    protected:
        int m_length;

        struct Node : public Object
        {
            T value;
            Node* next;
            Node* prev;
        };

        mutable struct : public Object
        {
            char reserved[sizeof(T)];
            Node* next;
            Node* prev;
        } m_header;

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
        DualLinkList()
        {
            m_header.next = NULL;
            m_header.prev = NULL;
            m_length = 0;
            m_step = 0;
            m_current = NULL;
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
                    Node* currentNode = position(i);
                    Node* nextNode = currentNode->next;
                    node->value = e;

                    node->next = nextNode;
                    currentNode->next = node;


                    if(currentNode != reinterpret_cast<Node*>(&m_header))
                    {
                        node->prev = currentNode;
                    }
                    else
                    {
                        node->prev = NULL;
                    }

                    if(nextNode != NULL)
                    {
                        nextNode->prev = node;
                    }

                    m_length++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to insert a node object");
                }
            }

            return ret;
        }

        virtual bool remove(int i)
        {
            bool ret = (0 <= i) && (i < m_length);

            if(ret)
            {
                Node* currentNode = position(i);
                Node* toDel = currentNode->next;
                Node* nextNode = toDel->next;

                currentNode->next = nextNode;

                if(m_current == toDel)
                {
                    m_current = m_current->next;
                }

                if(nextNode != NULL)
                {
                    nextNode->prev = toDel->prev;
                }

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

        virtual bool prev()
        {

            int i=0;

            while(!end() && (i<m_step))
            {

                i++;
                m_current = m_current->prev;
            }

            return (i == m_step);
        }

        virtual void clear()
        {
            while(m_length>0)
            {
                remove(0);
            }
        }

        ~DualLinkList()
        {
            clear();
        }
    };
}

#endif
