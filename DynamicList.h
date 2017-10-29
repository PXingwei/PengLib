#ifndef _DYNAMICLIST_H__
#define _DYNAMICLIST_H__
#include "SeqList.h"

namespace PengLib
{

    template <typename T>
    class DynamicList : public SeqList<T>
    {
    protected:
        int m_capacity;

    public:

        DynamicList(int capacity)
        {

            this->m_array = new T[capacity];

            if(this->m_array != NULL)
            {

                this->m_length = 0;
                this->m_capacity = capacity;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory for a dynamiclist object");
            }
        }

        int capacity() const
        {

            return m_capacity;
        }

        void resize(int newCapacity)
        {
            if(m_capacity != newCapacity)
            {

                T* array = new T[newCapacity];

                if(array != NULL)
                {

                    int newLen = ((newCapacity < this->m_length) ? newCapacity: this->m_length);

                    for(int i=0; i<newLen; i++)
                    {
                        array[i] = this->m_array[i];
                    }

                    T* temp = this->m_array;

                    this->m_array = array;
                    this->m_length = newLen;
                    this->m_capacity = newCapacity;

                    delete[] temp;
                }
                else
                {

                    THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory for a dynamiclist object");
                }
            }

        }

        ~DynamicList()
        {
            delete this->m_array;
        }
    };
}


#endif
