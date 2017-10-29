#ifndef _CIRCLELIST_H__
#define _CIRCLELIST_H__
#include "LinkList.h"

namespace PengLib
{
    template <typename T>
    class CircleList : public LinkList<T>
    {

    protected:
        typedef typename LinkList<T>::Node Node;

        Node* last() const
        {
            return this->position(this->m_length-1)->next;
        }

        void last_to_first() const
        {
            last()->next = this->m_header.next;
        }

        int mod(int i) const
        {
            return ((this->m_length == 0 )? 0 : (i % this->m_length));
        }

    public:

        bool insert(const T& e)
        {
            return insert(this->m_length, e);
        }

        bool insert(int i, const T& e)
        {
            bool ret = true;

            i = (i % (this->m_length+1));
            ret = LinkList<T>::insert(i, e);

            if(ret && (i==0))
            {
                last_to_first();
            }

            return ret;
        }

        bool remove(int i)
        {
            bool ret = true;
            i = mod(i);

            if(i == 0)
            {

                Node* toDel = this->m_header.next;

                if(toDel != NULL)
                {
                    this->m_header.next = toDel->next;
                    this->m_length--;

                    if(this->m_length > 0)
                    {
                        if(this->m_current == toDel)
                        {
                            this->m_current = this->m_current->next;
                        }

                        last_to_first();
                    }
                    else
                    {
                        this->m_header.next = NULL;
                        this->m_current = NULL;
                    }

                    this->destroy(toDel);
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = LinkList<T>::remove(i);
            }

            return ret;
        }

         T get(int i) const
        {
            i = mod(i);

            return LinkList<T>::get(i);
        }

        bool get(int i, T& e) const
        {
            i = mod(i);

            return LinkList<T>::get(i, e);
        }

        bool set(int i, const T& e)
        {
            i = mod(i);

            return LinkList<T>::set(i, e);
        }

        int find(const T& e) const
        {
            int ret = -1;
            Node* current = this->m_header.next;

            for(int i=0; i<this->m_length; i++)
            {
                if(current->value == e)
                {
                    ret = i;
                    break;
                }

                current = current->next;
            }

            return ret;
        }

        bool end()
        {
            return (this->m_length == 0) || (this->m_current == NULL);
        }

        bool move(int i, int step = 1)
        {
            i = mod(i);

            return LinkList<T>::move(i, step);
        }

        void clear()
        {

            while(this->m_length > 1)
            {
                remove(1);
            }

            if(this->m_length == 1)
            {

                Node* toDel = this->m_header.next;
                this->m_header.next = NULL;
                this->m_current = NULL;
                this->m_length = 0;

                this->destroy(toDel);

            }
        }
    };
}


#endif
