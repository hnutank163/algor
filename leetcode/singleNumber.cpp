#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <ext/hash_set>
#include <unordered_set>
using namespace std;
using namespace __gnu_cxx;
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

    vector<int> singleNumber2(vector<int> &nums)
    {
        list<int> li;
        list<int>::iterator iter;
        if(nums.size()<3)
            return nums;
        for(int i=0; i<(int)nums.size(); ++i)
        {
            if(li.empty())
                li.push_back(nums[i]);
            else{
                if( (iter=std::find(li.begin(), li.end(), nums[i])) != li.end())
                    li.erase(iter);
                else
                    li.push_back(nums[i]);
            }
        }

        return vector<int>(li.begin(), li.end());
    }

    vector<int> singleNumber3(vector<int> &nums)
    {
        if(nums.size()<3)
            return nums;
        hash_set<int> hs;
        std::pair<hash_set<int>::iterator, bool> p;
        for(int i=0; i<(int)nums.size(); ++i)
        {
            p = hs.insert(nums[i]);
            if(p.second == false)
                hs.erase(p.first);
        }
        vector<int> res = {0,0} ;
        int j=0;
        for(int i=0; i<(int)nums.size(); ++i)
        {
            if(hs.find(nums[i])!=hs.end())
                res[j++] = nums[i];
        }

        return res;
    }

    vector<int> singleNumber4(vector<int> &nums)
    {
        if(nums.size()<3)
            return nums;
        std::unordered_set<int> us;
        std::pair<unordered_set<int>::iterator, bool> p;
        for(int i=0; i<(int)nums.size(); ++i)
        {
            p = us.insert(nums[i]);
            if(p.second == false)
                us.erase(p.first);
        }
        vector<int> res = {0,0};
        int j=0;
        cout<<us.size()<<endl;
        for(auto i: us)
            cout<<i<<endl;
        for(int i=0; i<(int)nums.size(); ++i){
            if(us.find(nums[i]) != us.end())
                res[j++] = nums[i];
        }

        return res;
    }
};

int main(){
    vector<int> nums = {0,1,2,1,9,4,5,3,2,4,3};
    Solution sl;
    for(auto i: sl.singleNumber4(nums))
        cout<<i<<endl;
    return 0;
}
