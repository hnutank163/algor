#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/*
 * 给定一个数组a, 如果i<j && a[i]>2*a[j] 则计数+1
 * 计算数组周玲所有的满足该条件的对数"wq"
 *
 */
using namespace std;
class Solution
{
public:

    /**
     * @brief: reversePair
     *
     * @param nums
     *
     * @return
     */
    int reversePair(vector<int > &nums)
    {
        vector<long> vl;
        vector<long>::iterator iter;
        int sum = 0;
        for (int i = nums.size(); i >= 0; --i)
        {
            iter = ::upper_bound(vl.begin(), vl.end(), nums[i]);
            sum += iter - vl.begin();
            vl.insert(::upper_bound(vl.begin(), vl.end(), 1+2*nums[i]), 1+2*nums[i]);
        }

        return sum;
    }
};

int main(int argc, char *argv[])
{
    vector<int> v = {2,3,1,5,4,6};
    Solution sl;
    cout<<sl.reversePair(v)<<endl;

    return 0;
}
