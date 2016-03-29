#include <iostream>
#include <vector>
#include <boost/timer/timer.hpp>
#include <cstdlib>

using namespace std;

class Solution
{
public:
    vector< vector<int> > combine(int n, int k)
    {
        vector<vector<int> > vi;
        vector<int> tmp;

        for(int i=1 ;i<=n; ++i)
        {
            vector<vector<int> > v = combine_helper(i+1,n,k-1);
            for (auto j : v) {
                j.push_back(i);
                vi.push_back(j);
            }
        }
        return vi;
    }

    vector<vector<int> > combine_helper(int start, int end, int k)
    {
        vector< vector<int> > vi;
        if(k==1)
        {
            for(int i=start; i<=end; ++i)
            {
                vector<int> v;
                v.push_back(i);
                vi.push_back(v);
            }
            return vi;
        }
        else
        {
            vi = combine_helper(start+1, end, k-1);
        }
        return vi;
    }
};
int main(int argc, char *argv[])
{
    Solution sl;
    vector< vector<int> > vi = sl.combine(atoi(argv[1]), atoi(argv[2]));
    for (auto i : vi) {
        cout<<"[";
        for (auto j : i) {
            cout<<j;
        }
        cout<<"]";
    }
    return 0;
}
