//
// Created by TangXin on 2016/3/31.
//

#ifndef PROJECT_BINARYHEAP_HPP
#define PROJECT_BINARYHEAP_HPP

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
class BinaryHeap {
private:
    T *heap;
    size_t capacity;
    size_t size = 0;
private:
    int left(int index) {
        int i = 1 + (index << 1);
        if (i < size)
            return i;
        return -1;
    }

    int right(int index) {
        int i = 2 + (index << 1);
        if (i < size)
            return i;
        return -1;
    }

    int parent(int index) {
        int i = (index - 1) >> 1;
        if (i < 0)
            return -1;
        return i;
    }

public:
    BinaryHeap(size_t capacity_ = 32) : capacity(capacity_), size(0) {
        heap = new T[capacity];
    }

    ~BinaryHeap() { }

    void insert(const T &t) {
        heap[size++] = t;
        heapUp_no_recursive(size - 1);
    }

    void delete_min() {
        if (size == 0)
            return;


        heap[0] = heap[--size];
        heapDown_no_recursive(0);
    }

    T &get_min() { return heap[0]; }

    void heapUp(int index) {
        int parentIndex = parent(index);
        if (parentIndex >= 0 && heap[parentIndex] > heap[index]) {
            T temp = heap[parentIndex];
            heap[parentIndex] = heap[index];
            heap[index] = temp;
            heapUp(parentIndex);
        }
    }

    void heapUp_no_recursive(int index) {
        int parentIndex = parent(index);
        while (parentIndex >= 0 && heap[parentIndex] > heap[index]) {
            T temp = std::move(heap[parentIndex]);
            heap[parentIndex] = std::move(heap[index]);
            heap[index] = std::move(temp);
            index = parentIndex;
            parentIndex = parent(index);
        }
    }

    void heapDown(int index) {
        int left_ = left(index);
        int right_ = right(index);
        int minIndex = left_;
        if (minIndex < 0)
            return;
        if (right_ >= 0 && heap[right_] < heap[left_])
            minIndex = right_;

        if (minIndex > 0 && heap[minIndex] < heap[index]) {
            std::swap(heap[index], heap[minIndex]);
            heapDown(minIndex);
        }
    }

    void heapDown_no_recursive(int index) {
        int left_ = left(index);
        int right_ = right(index);
        int minIndex = left_;
        if (right_ >= 0 && heap[right_] < heap[left_])
            minIndex = right_;
        while (minIndex > 0 && heap[minIndex] < heap[index]) {
            T temp = std::move(heap[minIndex]);
            heap[minIndex] = std::move(heap[index]);
            heap[index] = std::move(temp);

            index = minIndex;
            left_ = left(index);
            right_ = right(index);
            minIndex = left_;
            if (right_ >= 0 && heap[right_] < heap[left_])
                minIndex = right_;
        }
    }

    void display() {
        for (auto t: heap)
            cout << t << " ";
        cout << endl;
    }
};

template<class T>
void heap_sort(T *begin, T *end) {
    T *temp = begin;
    BinaryHeap<T> bt(end - begin);
    timer tm;
    while (temp != end) {
        bt.insert(*(temp++));
    }
//    cout<<"create_heap time "<<tm.elapsed()<<endl;
    while (begin != end) {
        *(begin++) = bt.get_min();
        bt.delete_min();
    }
}

template<class T>
void heap_sort2(T *begin, T *end) {
    std::make_heap(begin, end);
    std::sort_heap(begin, end);
}

void BinaryHeap_test() {
    int a[] = {2, 1, 4, 3, 5, 8, 10, 9};
    heap_sort(a, a + 8);
    for (auto i: a)
        cout << i << " ";
    cout << endl;
}


#endif //PROJECT_BINARYHEAP_HPP
