#ifndef _SMARTPOINTER_H__
#define _SMARTPOINTER_H__

#include "Pointer.h"

namespace PengLib
{
/** This class is uesd to simulate the behavior of the primary pointer, 
    and can automatically free the pointer, when SmartPointer Objectd disappear */
template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL) : Pointer<T>(p)
    {

    }

    SmartPointer(const SmartPointer<T>& obj)
    {
        this->m_pointer = obj.m_pointer;

        const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

    }
    /** overload the = oprator */
    SmartPointer& operator = (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            //delete this->m_pointer;
            T* temp = this->m_pointer;

            this->m_pointer = obj.m_pointer;

            const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;

            delete temp;
        }

        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }
};

}

#endif // SMARTPOINTER_H
