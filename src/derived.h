#pragma once
#include <iostream>
using namespace std;
class Base
{
public:
   void func(){
       cout<<"in Base func\n";
   }

    virtual void func(int ){
        cout<<"in Base virtual func\n";
    }

    void func2(int,int ){
        func();
    }
};

class Derived :public Base
{
public:
    void func(){
        Base::func(1);
        cout<<"in Derived func\n";
    }
};

void Derived_test()
{
    Derived d;
    d.func();

    Base *b = new Derived();
    b->func();

}
