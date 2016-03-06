#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
int max_nums_1(const int *a, int n);
int max_nums_2(const int *a, int n);
int max_nums_3(const int *a, int n);

template<typename T>
void print(T begin, T end)
{
    for(T t=begin; t<end; ++t)
        std::cout<<*t<<" ";
    std::cout<<std::endl;
}

#endif
