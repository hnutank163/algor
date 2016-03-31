#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <ctime>

int max_nums_1(const int *a, int n);

int max_nums_2(const int *a, int n);

int max_nums_3(const int *a, int n);

class timer {
private:
    clock_t cl;
public:
    timer() {
        start();
    }

    void start() {
        cl = clock();
    }

    double elapsed() {
        return 1.0 * (clock() - cl) / CLOCKS_PER_SEC;
    }
};

template<typename T>
void print(T begin, T end) {
    for (T t = begin; t < end; ++t)
        std::cout << *t << " ";
    std::cout << std::endl;
}

template<class T>
inline static void Swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<class Iterator>
void bubble_sort(Iterator begin, Iterator end) {
    for (Iterator out = end; out != begin; --out) {
        for (Iterator in = begin;
        in < out - 1;
        ++in )
        {
            if (*in > *(in + 1))
                Swap(*in, *(in + 1));
        }
    }
}

template<class Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    Iterator mid = begin+(end-begin)/2;
    Iterator first = begin;
    Iterator last = end-1;
    while(first<last)
    {
        while(first<mid && *first<=*mid)
            ++first;

        while(last>mid && *last>=*mid)
            --last;

        if( first<last )
        {
            Swap(*first, *last);
            if(first == mid)
                mid = last;
            else if(last == mid)
                mid = first;
        }
    }
    if(begin < mid-1)
        quick_sort(begin, mid);
    if(mid+1 < end-1)
        quick_sort(mid+1, end);
}

template<class Iterator>
void merge_sort(Iterator begin, Iterator end)
{
    merge_sort_brige(begin, end-1, *begin);
}

template<class Iterator, class Object>
void merge_sort_brige(Iterator begin, Iterator end, const Object obj) //obj is used to translate type Object
{
    int len = end - begin + 1;
    Object *array = new Object[len];
    _merge_sort_brige(begin, end,  array);
    delete [] array;
}

template<class Iterator, class Object>
void _merge_sort_brige(Iterator begin, Iterator end, Object * array)
{
    if( begin < end )
    {
        Iterator mid = begin + (end-begin)/2;
        _merge_sort_brige(begin, mid, array);
        _merge_sort_brige(mid+1, end, array);
        merge_two_array(begin, mid, end, array);
    }
}

template<class Iterator, class Object>
void merge_two_array(Iterator begin, Iterator mid, Iterator end, Object * tmp)
{
     Iterator i = begin;
     Iterator j = mid+1;
     Object *before = tmp;
     while( i<=mid && j<=end )
     {
         if( *i < *j )
              *(tmp++) = *(i++);
         else
             *(tmp++) = *(j++);
     }

     while( i<=mid )
          *(tmp++) = *(i++);

     while( j<=mid )
         *(tmp++) = *(j++);

     while(before < tmp)
         *(begin++) = *(before++);
}
#endif
