#ifndef _SORT_H_
#define _SORT_H_
#include <iostream>
template<typename T>
void print(T *begin, T * end)
{
    for(T *t=begin; t<end; ++t)
       std::cout<<*t<<" " ;
    std::cout<<std::endl;
}

template<typename T>
void insert_sort(T *begin, T *end)
{
    T *i, *j;
    for(i=begin+1; i<end; ++i)
    {
        T tmp = *i;
        for(j=i-1; j>=begin; --j)
        {
            if(tmp>*j)
                break;
        }
        for(T *k = i; k>j+1; --k)
            *k = *(k-1);
        *(j+1) = tmp;
    }
}
#endif /* ifndef _SORT_H_ */
