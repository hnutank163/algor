#pragma once
#include <iostream>
using namespace std;
class Base
{
public:
    void m1()
    {
        cout << "in base m1\n";
    }
    void m2()
    {
        cout << "in base m2\n";
    }
    void m2(int)
    {
        cout << "in base m2(int)\n";
    }
};

class Derived :public Base
{
public:
    using Base::m2;
    void m2()
    {
        cout << "int drive m2\n";
    }
};

void Derived_test()
{
    Derived d;
    int x=0;
    d.m1();
    d.m2();
    d.m2(x);
}
