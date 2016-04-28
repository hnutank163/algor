#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<int> getRow(int rowIndex){
        vector<int> res ;
        if(rowIndex==0)
        {
            res.push_back(1);
            return res;
        }
        else
        {
            vector<int> temp = getRow(rowIndex-1);
            res.push_back(1);
            for(int i=1; i<(int)temp.size();++i){
                res.push_back(temp[i]+temp[i-1]);
            }
            res.push_back(1);
        }

        return res;
    }

    vector<int> getRow2(int rowIndex){
        vector<int> res;

        return res;
    }
};

int main()
{
    Solution sl;
    for(auto i: sl.getRow(3))
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
