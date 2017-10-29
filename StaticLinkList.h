#ifndef _STATICLINKLIST_H__
#define _STATICLINKLIST_H__
#include "LinkList.h"

namespace PengLib
{

    template <typename T, int N>
    class StaticLinkList : public LinkList<T>
    {
    protected:

        typedef typename LinkList<T>::Node Node;

        unsigned char m_space[N*sizeof(Node)];
        int m_used[N];

        struct SNode : public Node
        {
            void* operator new (unsigned int size, void* loc)
            {
                (void)size;
                return loc;
            }
        };

    public:
         Node* create()
        {
            SNode* ret = NULL;

            for(int i=0; i<N; i++)
            {
                if(!m_used[i])
                {
                    ret = reinterpret_cast<SNode*>(m_space) + i;
                    ret = new(ret) SNode();
                    m_used[i] = 1;
                    break;
                }
            }

            return ret;
        }

        void destroy(Node* pn)
        {
            SNode* space = reinterpret_cast<SNode*>(m_space);
            SNode* psn = dynamic_cast<SNode*>(pn);

            for(int i=0; i<N; i++)
            {
                if((space+i) == psn)
                {
                    m_used[i] = 0;
                    psn->~SNode();
                    break;
                }
            }
        }

        StaticLinkList()
        {
            for(int i=0; i<N; i++)
            {
                m_used[i] = 0;
            }
        }

        int capacity() const
        {
            return N;
        }

    };
}

#endif
