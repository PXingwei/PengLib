#ifndef _POINTER_H__
#define _POINTER_H__
#include "Object.h"

namespace PengLib
{
    /**This class is used to repalce the primary pointer. Its subclass is SmartPointer class and SharedPointer class*/
    template <typename T>
    class Pointer : public Object
    {
    protected:
        T* m_pointer;

    public:
        Pointer(T* p = NULL)
        {
            m_pointer = p;
        }
        /**This function is used to get the pointer's value*/
        T* get()
        {
            return m_pointer;
        }
        /**This function is used to get whether the the pointer is Null or not*/
        bool isNull()
        {
            return (m_pointer == NULL);
        }
        /**Overload the -> operator */
        T* operator ->()
        {
            return m_pointer;
        }
        /**Overload the * operator */
        T& operator *()
        {
            return *m_pointer;
        }
    };

}

#endif
