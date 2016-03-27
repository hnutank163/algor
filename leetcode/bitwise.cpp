//
// Created by tank on 16-3-27.
//
#include <iostream>
#include <cstdlib>
using namespace std;
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int i = n;
        while (i > m) {
            i = i&(i-1);
        }
        return i;
    }


    int rangeBitwiseAnd2(int m, int n)
    {
        return 1;
    }
};

int main(int argc, char **argv) {
    Solution sl;
    cout<<sl.rangeBitwiseAnd(atoi(argv[1]),atoi(argv[2]));
    return 0;
}

