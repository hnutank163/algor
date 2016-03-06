#include <iostream>
#include "common.h"
#include "Vector.hpp"
using namespace std;
#define LEN(a) sizeof(a)/sizeof(int)

void Vector_test()
{
    Vector<int> vi;
    vi.push_back(1);
    vi.push_back(2);
    vi.push_back(3);
    print(vi.begin(), vi.end());
    vi.pop_back();
    cout<<"back "<<vi.back()<<endl;
    print(vi.begin(), vi.end());
}

int main(int argc, char *argv[])
{
    int a[] = {1,-23,3,4,-5,6,7,-8,9};
    cout<<max_nums_1(a, LEN(a))<<endl;
    cout<<max_nums_2(a, LEN(a))<<endl;;
    Vector_test();
    return 0;
}
