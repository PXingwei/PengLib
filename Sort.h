#ifndef _SORT_H__
#define _SORT_H__
#include "Object.h"
#include "Array.h"

namespace PengLib
{
    class Sort : public Object
    {
    private:
        Sort();
        Sort(const Sort&);
        Sort& operator = (const Sort&);

        template <typename T>
        static void Swap(T& a, T& b)
        {
            T c(a);
            a = b;
            b = c;
        }

        template <typename T>
        static void Merge(T src[], T helper[], int begin, int end, bool min2max=true)
        {
            if(begin < end)
            {
                int mid = (begin + end) / 2;



                Merge(src, helper, begin, mid, min2max);
                Merge(src, helper, mid+1, end, min2max);
                Merge(src, helper, begin, mid, end, min2max);
            }
        }

        template <typename T>
        static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max=true)
        {
            int i = begin;
            int j = mid + 1;
            int k = begin;

            while((i<=mid) && (j<=end))
            {
                if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
                {
                    helper[k++] = src[i++];
                }
                else
                {
                    helper[k++] = src[j++];
                }
            }

            while(i<=mid)
            {
                helper[k++] = src[i++];
            }

            while(j<=end)
            {
                helper[k++] = src[j++];
            }

            for(int s=begin; s<=end; s++)
            {
                src[s] = helper[s];
            }

        }

        template <typename T>
        static void Quick(T array[], int begin, int end, bool min2max=true)
        {
            if(begin < end)
            {
                int pv = Partition(array, begin, end, min2max);
                Quick(array, begin, pv-1, min2max);
                Quick(array, pv+1, end, min2max);
            }
        }

        template <typename T>
        static int Partition(T array[], int begin, int end, bool min2max=true)
        {
            T pv = array[begin];

            while(begin < end)
            {
                while((begin<end) && (min2max ? (array[end]>pv) : (array[end]<pv)))
                {
                    end--;
                }

                Swap(array[end], array[begin]);

                while((begin<end) && (min2max ? (array[begin]<=pv) : (array[begin]>=pv)))
                {
                    begin++;
                }

                Swap(array[end], array[begin]);
            }

            array[begin] = pv;
            return begin;
        }

    public:

        template <typename T>
        static void select(T array[], int len, bool min2max=true)
        {
            for(int i=0; i<len; i++)
            {
                int minOrmax = i;
                for(int j=i+1; j<len; j++)
                {
                    if(min2max ? (array[minOrmax] > array[j]) : (array[minOrmax] < array[j]))
                    {
                        minOrmax = j;
                    }

                }
                if(minOrmax != i)
                {
                    Swap(array[minOrmax], array[i]);
                }
            }
        }

        template <typename T>
        static void insert(T array[], int len, bool min2max=true)
        {
            for(int i=1; i<len; i++)
            {
                T e = array[i];
                int k = i;
                for(int j=i-1; (j>=0) && (min2max ? (e < array[j]) : (e > array[j])); j--)
                {
                        array[j+1] = array[j];
                        k = j;
                }

                if(k != i)
                {
                    array[k] = e;
                }
            }
        }

        template <typename T>
        static void Buble(T array[], int len, bool min2max=true)
        {
            bool exchange = true;

            for(int i=0; i<len && exchange; i++)
            {
                exchange = false;

                for(int j=len-1; j>i; j--)
                {
                    if (min2max ? (array[j] <array[j-1]) : (array[j] > array[j-1]))
                    {
                        Swap(array[j], array[j-1]);
                        exchange = true;
                    }
                }
            }
        }


        template <typename T>
         static void Shell(T array[], int len, bool min2max=true)
         {
             int d = len;

             do
             {
                 d = d/3 + 1;
                 for(int i = d; i<len; i+=d)
                 {
                     for(int s=i; (s<i+d) && (s<len); s++)
                     {
                         int k = s;
                         T e = array[s];

                         for (int j = s-d; j >= 0 && (min2max ? (array[j]>e) : (array[j]<e)); j-=d)
                         {
                             array[j+d] = array[j];
                             k = j;
                         }

                         if(k != s)
                         {
                             array[k] = e;
                         }
                     }


                 }
             }while(d > 1);
         }

         template <typename T>
         static void Merge(T array[], int len, bool min2max=true)
         {
             T* helper = new T[len];

             if(helper != NULL)
             {
                 Merge(array, helper, 0, len-1, min2max);
             }

             delete[] helper;
         }

         template <typename T>
         static void Quick(T array[], int len, bool min2max=true)
         {
             Quick(array, 0, len-1, min2max);
         }

         template <typename T>
         static void select(Array<T>& array, bool min2max=true)
         {
            return select(array.array(), array.length(), min2max);
         }

         template <typename T>
         static void insert(Array<T>& array, bool min2max=true)
         {
            return insert(array.array(), array.length(), min2max);
         }

         template <typename T>
         static void Buble(Array<T>& array, bool min2max=true)
         {
            return Buble(array.array(), array.length(), min2max);
         }

         template <typename T>
         static void Shell(Array<T>& array, bool min2max=true)
         {
            return Shell(array.array(), array.length(), min2max);
         }

         template <typename T>
         static void Merge(Array<T>& array, bool min2max=true)
         {
            return Merge(array.array(), array.length(), min2max);
         }

         template <typename T>
         static void Quick(Array<T>& array, bool min2max=true)
         {
            return Quick(array.array(), array.length(), min2max);
         }

    };
}


#endif
