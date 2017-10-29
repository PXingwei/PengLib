#ifndef _STATICLIST_H__
#define _STATICLIST_H__
#include "SeqList.h"

namespace PengLib
{
    template <typename T, int N>
    class StaticList : public SeqList<T>
    {
    protected:
        T m_space[N];

    public:

        StaticList()
        {

            this->m_array = m_space;
            this->m_length = 0;
        }

        int capacity() const
        {
            return N;
        }

    };

}


#endif // STATICLIST_H
