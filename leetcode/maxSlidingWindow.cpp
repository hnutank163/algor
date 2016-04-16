#include <vector>
#include <iostream>
#include <deque>
using namespace std;

class Solution{

public:
    int max(vector<int>::iterator iter1, vector<int>::iterator iter2){
        int maxNum = *iter1;
        if(iter1>=iter2)
            return 0;
        while(iter1!=iter2)
        {
            if(maxNum < *iter1)
                maxNum = *iter1;
            ++iter1;
        }

        return maxNum;
    }

    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> vi;
        if((int)nums.size() < k)
            return vi;
        vi.assign(nums.begin(), nums.end()-k+1);
        int size = nums.size();
        for(int i= 0;i<size;++i)
        {
            for(int j=i-(k-1); j<i+1; ++j){

                if(j>=0 && j<size-k+1)
                    vi[j] = std::max(vi[j],nums[i]);
            }
        }
        return vi;
    }

    vector<int> maxSlidingWindow2(vector<int> &nums, int k)
    {
        vector<int> vi;
        if( (int)nums.size()<k || k==0)
            return vi;
        vi.assign(nums.begin(), nums.end()-k+1);
        int size = nums.size();
        for(int i=0; i<size-k+1; i+=2){
            int temp = max(nums.begin()+i+1,nums.begin()+i+k);
            cout<<"temp "<<temp<<endl;
            vi[i] = std::max(nums[i],temp);
            vi[i+1] = std::max(nums[i+k],temp);
        }
        vi[size-k] = max(nums.end()-k,nums.end());
        return vi;
    }

    vector<int> maxSlidingWindow3(vector<int> &nums, int k)
    {
        int size = nums.size();
        vector<int> vi;
        if(k==0)
            return vi;
        deque<int> dq;
        for(int i=0; i<size; ++i){
            while( !dq.empty() && dq.front()<=i-k)
                dq.pop_front();
            while( !dq.empty() && nums[dq.back()]<nums[i])
                dq.pop_back();
            dq.push_back(i);
            if(i>=k-1)
                vi.push_back(nums[dq.front()]);
        }
        return vi;
    }

};


int main(){
    Solution sl;
    int a[ ] = {-6,-10,-7,-1,-9,9,-8,-4,10,-5,2,9,0,-7,7,4,-2,-10,8,7};
    vector<int> vi;
    vi.assign(a,a+20);
    vector<int> v = sl.maxSlidingWindow2(vi,7);
    for(auto i:v)
        cout<<i<< " ";
    cout<<endl;
    vector<int> v2 = sl.maxSlidingWindow3(vi,7);
    for(auto i:v2)
        cout<<i<< " ";
    cout<<endl;
}
