#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "HashTable.hpp"
#include "common.h"
#include "Vector.hpp"
#include "Stack.hpp"
#include "BinaryTree.hpp"
#include "BinaryHeap.hpp"
#include "derived.h"
#include "HashTable.hpp"

using namespace std;
#define LEN(a) sizeof(a)/sizeof(int)

void Vector_test() {
    Vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    print(vi.begin(), vi.end());
    vi.pop_back();
    cout << "back " << vi.back() << endl;
    print(vi.begin(), vi.end());
}

void Stack_test() {
    cout << "stack test\n";
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout << st << endl;
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    cout << st << endl;
    cout << "end stack test\n";
}

int polish(char *p) {
    Stack<int> st;
    char *q = p;

    while (*q) {
        if (*q >= '0' && *q <= '9')
            st.push(*q - '0');
        else {
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();

            switch (*q) {
                case '+':
                    st.push(a + b);
                    break;

                case '-':
                    st.push(a - b);
                    break;

                case '*':
                    st.push(a * b);
                    break;

                case '/':
                    st.push(a / b);
                    break;
            }
        }

        ++q;
    }

    return st.top();
}

void generate_big_array(int num, int size, int **a) {
    for (int i = 0; i < size; ++i) {
        int n = rand();
        for (int j = 0; j < num; ++j)
            a[j][i] = n;
    }
}

void sort_correctness_test() {
    int a[4][10] = {{2, 1, 3, 5, 4, 7, 6, 8, 10, 9},
                    {2, 1, 3, 5, 4, 7, 6, 8, 10, 9},
                    {2, 1, 3, 5, 4, 7, 6, 8, 10, 9},
                    {2, 1, 3, 5, 4, 7, 6, 8, 10, 9}};
    SORT::sort_heap(a[0], a[0] + 10);
    heap_sort2(a[1], a[1] + 10);
    std::sort(a[2], a[2] + 10);
    heap_sort(a[3], a[3] + 10);
    print(a[0], a[0] + 10);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            try {
                assert((1 + j) == a[i][j]);
            }
            catch (std::exception &e) {
                cout << e.what() << endl;
            }
        }
    }
}

void sort_speed_test() {
    int num = 4;
    int size = 3000000;
    int **a = new int *[num];
    for (int i = 0; i < num; ++i)
        a[i] = new int[size];

    generate_big_array(num, size, a);
    timer tm;
    std::make_heap(a[0], a[0] + size);
    std::sort_heap(a[0], a[0] + size);
    cout << tm.elapsed() << endl;
    tm.start();
    SORT::sort_heap(a[1], a[1] + size);
    cout << tm.elapsed() << endl;
    tm.start();
    heap_sort(a[2], a[2] + size);
    cout << tm.elapsed() << endl;
    tm.start();
    std::sort(a[3], a[3] + size);
    cout << tm.elapsed() << endl;
}

int main(int, char **) {
    sort_correctness_test();
    sort_speed_test();
//       BinaryHeap_test();
    return 0;
}
