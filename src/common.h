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

namespace SORT {
    template<class Iterator>
    void quick_sort(Iterator begin, Iterator end);

    template<class Iterator>
    void merge_sort(Iterator begin, Iterator end);

    template<class Iterator, class Object>
    void merge_sort_bridge(Iterator begin, Iterator end, const Object obj);

    template<class Iterator, class Object>
    void _merge_sort_bridge(Iterator begin, Iterator end, Object *array);

    template<class Iterator, class Object>
    void merge_two_array(Iterator begin, Iterator mid, Iterator end, Object *tmp);

//
    void heapsort(int *a, int n);

    void build_maxheap(int *a, int n);

    void max_heap(int *a, int i, int n);

//
    template<class T>
    void heapUp(T *begin, T *iter);

    template<class T>
    void heapDown(T *begin, T *end, T *iter);

    template<class T>
    void heapDown(T *begin, T *end, T *iter) {
        T *left = iter + (iter - begin) + 1;
        T *right = iter + (iter - begin) + 2;
        T *minIndex = left;
        if (right < end) {
            if (*right > *left)
                minIndex = right;
        }
        if (minIndex < end && *iter < *minIndex) {
            T t = std::move(*iter);
            *iter = std::move(*minIndex);
            *minIndex = std::move(t);
  //          std::swap(*iter, *minIndex);
            heapDown(begin, end, minIndex);
        }
    }
//

    template<class T>
    void heapUp(T *begin, T *iter) {
        T *parent = begin + (iter - begin - 1) / 2;
        if (*parent < *iter) {
            T t = std::move(*parent);
            *parent = std::move(*iter);
            *iter = std::move(t);
   //         std::swap(*parent, *iter);
            heapUp(begin, parent);
        }
    }

    template<class T>
    void make_heap(T *begin, T *end) {
        for (T *iter = begin + (end - begin) / 2; iter < end; ++iter) {
            heapUp(begin, iter);
        }
    }

    template<class T>
    void sort_heap(T *begin, T *end) {
//        timer tm;
        make_heap(begin, end);
//        std::cout<<"make heap time "<<tm.elapsed()<<std::endl;
//        std::cout<<"after make heap"<<std::endl;
//        for(T *i=begin; i!=end; ++i)
//            std::cout<<*i<<" ";
//        std::cout<<std::endl;
        for (T *iter = end - 1; iter > begin; --iter) {
           // std::swap(*iter, *begin);
            T temp = std::move(*iter);
            *iter = std::move(*begin);
            *begin = std::move(temp);
            heapDown(begin, iter, begin);
        }
    }


    template<class Iterator, class Object>
    void merge_two_array(Iterator begin, Iterator mid, Iterator end, Object *tmp) {
        Iterator i = begin;
        Iterator j = mid + 1;
        Object *before = tmp;
        while (i <= mid && j <= end) {
            if (*i < *j)
                *(tmp++) = *(i++);
            else
                *(tmp++) = *(j++);
        }

        while (i <= mid)
            *(tmp++) = std::move(*(i++));

        while (j <= mid)
            *(tmp++) = std::move(*(j++));

        while (before < tmp)
            *(begin++) = std::move(*(before++));
    }

    template<class Iterator, class Object>
    void _merge_sort_bridge(Iterator begin, Iterator end, Object *array) {
        if (begin < end) {
            Iterator mid = begin + (end - begin) / 2;
            _merge_sort_bridge(begin, mid, array);
            _merge_sort_bridge(mid + 1, end, array);
            merge_two_array(begin, mid, end, array);
        }
    }

    template<class Iterator, class Object>
    void merge_sort_bridge(Iterator begin, Iterator end, const Object obj) {
        int len = end - begin + 1;
        Object *array = new Object[len];
        _merge_sort_bridge(begin, end, array);
        delete[] array;
    }

    template<class Iterator>
    void merge_sort(Iterator begin, Iterator end) {
        merge_sort_bridge(begin, end - 1, *begin);
    }

    template<class Iterator>
    void quick_sort(Iterator begin, Iterator end) {
        Iterator mid = begin + (end - begin) / 2;
        Iterator first = begin;
        Iterator last = end - 1;
        while (first < last) {
            while (first < mid && *first <= *mid)
                ++first;

            while (last > mid && *last >= *mid)
                --last;

            if (first < last) {
                std::swap(*first, *last);
                if (first == mid)
                    mid = last;
                else if (last == mid)
                    mid = first;
            }
        }
        if (begin < mid - 1)
            quick_sort(begin, mid);
        if (mid + 1 < end - 1)
            quick_sort(mid + 1, end);
    }

}
#endif
