#include <iostream>
using namespace std;

//Give n, how many binary-search-tree tat can store 1-n.
//
class Solution{
public:
    int numTrees(int n)
    {
        int count=0;
        if(n==0 || n==1)
            return 1;
        for(int i=0; i<n; ++i)
            count += numTrees(i)*numTrees(n-i-1);

        return count;
    }

    int numTrees2(int n){
        int a=1;
        int b=1;
        int count = 0;
        while(n--){
            count += a*b;
            a = b;
            b = count;
        }

        return count;
    }
};

int main(int argc, char *argv[])
{
    Solution sl;
    cout<<sl.numTrees(1)<<" "<<sl.numTrees(2)<<" "<<sl.numTrees(3)<<" "
        <<sl.numTrees(4)<<endl;
    return 0;
}
