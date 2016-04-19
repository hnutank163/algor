#include <vector>
#include <iostream>
using namespace std;

class Solution{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int size = nums.size();
        vector<int> res(size,0);
        for(int i=size-1; i>=0; --i)
        {
            for(int j=i+1; j<size; ++j){
                if(nums[i]>nums[j])
                {
                    res[i] = 1+res[j];
                    break;
                }
            }
        }

        return res;
    }
};


int main(){
    vector<int> vi = {5,2,6,1};
    Solution sl;
    vector<int> res = sl.countSmaller(vi);
    for(auto i: res)
        cout<<i<<endl;
    return 0;
}
