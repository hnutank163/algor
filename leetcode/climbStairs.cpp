#include <iostream>
#include <cstdlib>
#include <boost/timer.hpp> 
using namespace std;
class Solution
{
public:
    /*
     * n个阶梯的楼梯，每次可以走一步或者两步，求所有走法
     * 用递归会导致计算时间过长 :)
     * */
    int climbStairs(int n)
    {
        int *a  = new int[n];
        a[0] = 1;
        a[1] = 2;
        for(int i=2; i<n; ++i)
        {
            a[i] = a[i-1] + a[i-2];
        }
        int re = a[n-1];
        delete [] a;
        return re;
    }

    int climbStairs2(int n)
    {
        int a = 1;
        int b = 1;
        while(n--)
        {
            a = (b+=a) - a;
        }

        return a;
    }

    int climbStairs3(int n)
    {
        int a = 1;
        int b = 1;
        while(n--)
        {
            b = a+b;
            a = b-a;
        }

        return a;
    }
};


int main(int , char ** argv)
{
    boost::timer tm;
    Solution sl;
    cout<<sl.climbStairs(atoi(argv[1]))<<endl;
    cout<<tm.elapsed()<<endl;
    tm.restart();
    cout<<sl.climbStairs2(atoi(argv[1]))<<endl;
    cout<<tm.elapsed()<<endl;
    tm.restart();
    cout<<sl.climbStairs3(atoi(argv[1]))<<endl;
    cout<<tm.elapsed()<<endl;
    return 0;
}
