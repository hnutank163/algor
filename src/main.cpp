#include <iostream>
#include <cmath>
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
            *(a + j)[i] = n;
    }
}

int main(int, char **) {
    int nums = 4;
    int size = 10000;
    int **a = new int *();
    for (int i = 0; i < nums; ++i)
        *a = new int[size];

    generate_big_array(nums,size,a);
    timer tm;
//    unordered_map_test();
//    HashTable_test();
    //Derived_test();
    /*   int a[] = { 1, -23, 3, 4, -5, 6, 7, -8, 9 };
    cout << max_nums_1(a, LEN(a)) << endl;
    cout << max_nums_2(a, LEN(a)) << endl;;
    Vector_test();
    Stack_test();

    char *p = "6532 + 8 * +3 +*";
    cout << p << " polish " << polish(p) << endl;
    cout << "binary tree test\n";
    BinaryTree_Test();*/
    //  unordered_map_test();
    heap_sort(a[0],a[0]+size);
    cout << tm.elapsed() << endl;
    tm.start();
    bubble_sort(a[1], a[1] + size);
    cout << tm.elapsed() << endl;
    return 0;
}
