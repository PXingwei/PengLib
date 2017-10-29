#ifndef _DYNAMICARRAY_H__
#define _DYNAMICARRAY_H__
#include "Array.h"

namespace PengLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    void init(T* array, int len)
    {

        if(array != NULL)
        {

            this->m_array = array;
            this->m_length = len;
        }
        else
        {

            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create DynamicArray Object");
        }
    }

    T* copy(T* array, int len, int newLen)
    {

        T* ret = new T[newLen];

        if(ret != NULL)
        {

            int size = (len < newLen) ? len : newLen;

            for(int i=0; i<size; i++)
            {

                ret[i] = array[i];
            }
        }

        return ret;
    }

    void update(T* array, int len)
    {
        if(array != NULL)
        {

            T* temp = this->m_array;

            this->m_array = array;
            this->m_length = len;

            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to update a DynamicArray Object");
        }
    }

public:

    DynamicArray(int n)
    {

        init(new T[n], n);
    }

    DynamicArray(const DynamicArray<T>& obj)
    {


        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {


            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    void resize(int length)
    {

        if(this->m_length != length)
        {

            update(copy(this->m_array, this->m_length, length), length);
        }
    }

    int length() const
    {

        return m_length;
    }

    ~DynamicArray()
    {

        delete[] this->m_array;
    }

};

}

#endif
