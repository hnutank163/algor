#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution{
public:
    //give an array of numbers, only two number appear once, other appear twice,
    //such as[1,2,3,4,1,2,3,4,5,6] , return [5,6]
    vector<int> singleNumber(vector<int> & nums)
    {
        if(nums.size()<3)
            return nums;
        vector<int> res;
        vector<int> temp;
        temp.assign(nums.begin(), nums.end());
        std::sort(temp.begin(), temp.end());
        res.push_back(temp[0]);
        res.push_back(temp[temp.size()-1]);
        int i=1;
        int j=nums.size()-2;;
        int hasi = 0; int hasj=0;
        while(i<=j)
        {
            if(res[0] != temp[i])
                hasi = 1;
            else{
                while(res[0] == temp[i++])
                {
                    res[0] = temp[i++];
                }
            }
            if(res[1] != temp[j])
                hasj = 1;
            else{
                while(res[1] == temp[j--])
                    res[1] = temp[j--];
            }
        }

        return res;
    }
};

int main(){
    vector<int> nums = {0,1,2,2};
    Solution sl;
    for(auto i: sl.singleNumber(nums))
        cout<<i<<endl;
    return 0;
}
