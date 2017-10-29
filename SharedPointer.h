#ifndef _SHAREDPOINTER_H__
#define _SHAREDPOINTER_H__

#include "Pointer.h"
#include <cstdlib>

namespace PengLib {

    template <typename T>
    class SharedPointer : public Pointer<T>
    {
    protected:
        int* m_int;

        void assign(const SharedPointer<T>& obj)
        {
            m_int = obj.m_int;
            this->m_pointer = obj.m_pointer;

            if(m_int != NULL) {

                (*m_int)++;
            }
        }

    public:

        SharedPointer(T* p = NULL) : m_int(NULL)
        {

            if(p)
            {

                m_int = reinterpret_cast<int*>(std::malloc(sizeof(int))); //maybe an error

                if(m_int != NULL)
                {

                    *m_int = 1;
                    this->m_pointer = p;
                }
                else
                {

                    THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory to create SharedPointer object");
                }
            }
        }

        SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
        {

                assign(obj);
        }

        SharedPointer<T>& operator = (const SharedPointer<T>& obj)
        {

            if(this != &obj)
            {

                clear();

                assign(obj);
            }
        }

        void clear()
        {

            T* temp_pointer = this->m_pointer;
            int* temp_int = m_int;

            m_int = NULL;
            this->m_pointer = NULL;

            if(temp_int != NULL)
            {
                *temp_int--;
            }

            if(*temp_int == 0)
            {
                free(temp_int);
                delete temp_pointer;
            }
        }

        ~SharedPointer()
        {
            clear();
        }
    };
}

#endif
