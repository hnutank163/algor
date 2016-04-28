#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

//remove duplicate char in string
class Solution{
public:
    string removeDuplicateLetters(string s)
    {
        unordered_set<char> us;
        for(char ch: s)
            us.insert(ch);
        return string(us.begin(), us.end());
    }

    string removeDuplicateLetters2(string s)
    {
        int count[256] ={0};
        for(char ch:s)
            count[ch] ++;

        string res = " ";
        bool inresult[256] = {};

        for(auto ch: s)
        {
            --count[ch];
            if(inresult[ch])
                continue;
            while( ch<res.back() && count[res.back()])
            {
                inresult[res.back()] = false;
                res.pop_back();
            }
            res += ch;
            inresult[ch] = true;
        }

        return res.substr(1);
    }
};

int main()
{
    Solution sl;
    cout<<sl.removeDuplicateLetters2("cbacdcbc");
}
