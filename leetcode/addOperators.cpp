#include <vector>
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;

class Solution{
public:
    vector<string> addOperators(string num, int target)
    {
        vector<string> res;
        if(num.empty())
            return res;
        else{
            for(int i=1; i<=static_cast<int> (num.size()); ++i)
            {
                string s = num.substr(0,i);
                long cv = stol(s);
                dfs(res, num, target, s, i, cv, cv, '#');
            }
        }

        return res;
    }

    void dfs(vector<string> &res, string num, int target,string cur, int pos,
            long cv, long pv,  const char op){
        //cout<<pos<<" "<<cv<<endl;
        if(pos == (int)num.size() && cv==target)
            res.push_back(cur);
        else{
            for(int i=pos+1; i<=(int)num.size();++i){
                string t = num.substr(pos,i-pos);
                long now = stol(t);
                if(std::to_string(now).size()!=t.size())
                    continue;
                dfs(res, num, target, cur+"+"+t, i, cv+now, now, '+');
                dfs(res, num, target, cur+"-"+t, i, cv-now, now, '-');
                long val = 0;
                if(op=='-')
                    val = cv+pv-pv*now; //such as: 2-3*4 = (2-3)+3-3*4；
                else if(op=='+')            //2+3*4 = (2+3)-3+3*4;
                    val = cv-pv+pv*now;
                else                            //1+2*3*4 = 1+6*4  so we keep last operation, there is '+'
                    val = pv*now;
                dfs (res, num, target, cur+"*"+t, i, val, pv*now, op);
            }
        }
    }
};

int main(int argc, char **argv)
{
    cout<<"argc "<<argc<<endl;
    if(argc<3){
        cerr<<"usage: string target\n";
        exit(1);
    }
    string s(argv[1]);
    Solution sl;
    for(auto el:sl.addOperators(s,atoi(argv[2])))
        cout<<el<<endl;
    return 0;
}
