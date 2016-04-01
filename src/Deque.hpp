//
// Created by TangXin on 2016/4/1.
//

#ifndef PROJECT_DEQUE_HPP
#define PROJECT_DEQUE_HPP

#include <iostream>
#include <deque>

using namespace std;

template<class T>
class Deque {
private:
    struct Node {
        T *pre;
        T *next;
        T *cur;

        Node(const T &t = T(), T *pre_ = nullptr, T *next_ = nullptr) {
            pre = pre_;
            next = next_;
            cur = new T(t);
        }

        T &operator*() {
            return *cur;
        }

        Node &operator++() {
            this->next = this;
            return *this;
        }

        friend bool operator==(const Node &lhs, const Node &rhs) {
            return (lhs.pre == rhs.pre) && (lhs.next == rhs.next);
        }

        friend bool operator!=(const Node &lhs, const Node &rhs) {
            return !((lhs.pre == rhs.pre) && (lhs.next == rhs.next));
        }
    };


private:
    Node *head;
    Node *tail;
    size_t size;

public:
    typedef Node iterator;

    Deque() : size(0), head(nullptr), tail(nullptr) { }

    ~Deque() { }

    void push_front(const T &t) {
        if (head == nullptr)
            tail = head = new Node(t);
        else {
            head = (head->pre = new Node(t, nullptr, head));
        }
    }

    void push_back(const T &t) {
        if (head == nullptr)
            tail = head = new Node(t);
        else {
            tail = (tail->next = new Node(t, tail, nullptr));
        }
    }

    void display() {
        Node *node = head;
        while (node) {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    iterator begin() const { return *head; }

    iterator end() const { return *tail; }

};

//template<class T>
//bool operator==(const typename Deque<T>::iterator &lhs, const typename Deque<T>::iterator &rhs) {
//
//}
//
//template<class T>
//bool operator!=(const typename Deque<T>::iterator &lhs, const typename Deque<T>::iterator &rhs) {
//    return !(lhs == rhs);
//}

void Deque_test() {
    Deque<int> d;
    d.push_front(2);
    d.push_front(1);
    d.push_back(3);
    d.push_back(4);
    Deque<int>::iterator iter = d.begin();
    while (iter != d.end()) {
        cout << *iter << " ";
        ++iter;
    }
    cout << endl;
}

#endif //PROJECT_DEQUE_HPP
