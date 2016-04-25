#include <iostream>
#include <vector>
using namespace std;

class Solution{
    public:
        void moveZeroes(vector<int> &nums)
        {
            vector<int>::iterator left = nums.begin();
            vector<int>::iterator pos = nums.begin();
            while(left<nums.end())
            {
                if(*left != 0){
                    std::swap(*left, *pos);
                    ++pos;
                }
                ++left;
            }
        }
};


int main()
{
    Solution sl;
    vector<int> vi = {0,1,0,3,12};
    sl.moveZeroes(vi);
    for(auto i:vi)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
