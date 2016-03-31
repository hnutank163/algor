//
// Created by TangXin on 2016/3/31.
//

#ifndef PROJECT_BINARYHEAP_HPP
#define PROJECT_BINARYHEAP_HPP

#include <iostream>
#include <vector>

using namespace std;

template<class T>
class BinaryHeap {
private:
    vector<T> heap;
private:
    int left(int index) {
        int i = 2 * index + 1;
        if (i < heap.size())
            return i;
        return -1;
    }

    int right(int index) {
        int i = 2 * index + 2;
        if (i < heap.size())
            return i;
        return -1;
    }

    int parent(int index) {
        int i = (index - 1) / 2;
        if (i < 0)
            return -1;
        return i;
    }

public:
    BinaryHeap() { }

    ~BinaryHeap() { }

    void insert(const T &t) {
        heap.push_back(t);
        heapUp(heap.size() - 1);
    }

    void delete_min() {
        if (heap.empty())
            return;
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        heapDown(0);
    }

    T &get_min() { return heap[0]; }

    void heapUp(int index) {
        int parentIndex = parent(index);
        if (index >= 0 && heap[parentIndex] > heap[index]) {
            T temp = heap[parentIndex];
            heap[parentIndex] = heap[index];
            heap[index] = temp;
            heapUp(parentIndex);
        }
    }

    void heapDown(int index) {
        int left_ = left(index);
        int right_ = right(index);
        int minIndex = -1;
        if (left_ >= 0 && right_ >= 0)
            minIndex = left_ < right_ ? left_ : right_;
        if (minIndex>0 && heap[minIndex] < heap[index]) {
            int temp = heap[minIndex];
            heap[minIndex] = heap[index];
            heap[index] = temp;
            heapDown(minIndex);
        }
    }

    void display() {
        typename vector<T>::iterator iter = heap.begin();
        while (iter != heap.end())
            cout << *(iter++) << " ";
        cout << endl;
    }
};

template<class T>
void heap_sort(T *begin, T *end) {
    T *temp = begin;
    BinaryHeap<T> bt;
    while (temp != end) {
        bt.insert(*(temp++));
    }
    while (begin != end) {
        *(begin++) = bt.get_min();
        bt.delete_min();
    }
}

void BinaryHeap_test() {
    int a[] = {2, 1, 4, 3, 5};
    heap_sort(a, a + 5);
    for (auto i: a)
        cout << i << " ";
    cout << endl;
}


#endif //PROJECT_BINARYHEAP_HPP
