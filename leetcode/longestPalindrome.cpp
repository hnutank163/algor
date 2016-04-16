#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution{

public:

    void helper(string &s,string::iterator &left, string::iterator &right){
        while(left>=s.begin() && right<s.end() &&
                (*(left)==*(right)) )
        {
            --left;++right;
        }

    }

    string longestPalindrome(string s){
        if(s.size()<=1)
            return s;
        if(s.size()==2)
        {
            if(s[0]==s[1])
                return s;
            return string(1,s[0]);
        }
        int size = s.size();
        string::iterator mid = s.begin()+size/2;
        string::iterator left = mid-1;
        string::iterator right = mid;
        string::iterator iter1 = mid-1;
        string::iterator iter2 = mid;
        int need1 = 1;
        int need2 = 1;
        string::iterator temp1,temp2;
        while(need1+need2)
        {
            if(need1){
                int i=1;
                int j=1;
                temp1 = left-1;
                temp2 = left+1;
                helper(s,temp1, temp2);

                if(iter2-iter1 < temp2-temp1-2){
                    iter1 = temp1+1;
                    iter2 = temp2;
                }
                if(2*(1+left-s.begin())+1 <iter2-iter1)
                    i = 0;
                temp1 = right-1;
                temp2 = right+1;
                helper(s,temp1, temp2);
                if(iter2-iter1 < temp2-temp1-2){
                    iter1 = temp1+1;
                    iter2 = temp2;
                }
                if(1+2*(1+s.end()-right) < iter2-iter1)
                    j = 0 ;
                if(i==0 && j==0)
                    need1 = 0;
            }

            if(need2){
                int i=1;
                int j=1;
                temp1 = left;
                temp2 = left+1;
                helper(s,temp1, temp2);
                if(iter2-iter1 < temp2-temp1-1){
                    iter1 = temp1+1;
                    iter2 = temp2;
                }
                if( 2*(1+left-s.begin())<iter2-iter1)
                    i = 0;
                temp1 = right;
                temp2 = right+1;

                helper(s,temp1, temp2);
                if(iter2-iter1 < temp2-temp1-1){
                    iter1 = temp1+1;
                    iter2 = temp2;
                }
                if( 2*(1+s.end() - right) < iter2-iter1)
                    j = 0;
                if(i==0 && j==0)
                    need2 = 0;
            }
            --left; ++right;
            if(need1+need2 == 0)
                break;
        }

        return string(iter1,iter2);
    }
};


int main(){
    Solution sl;
    string s("bbbb");
    cout<<sl.longestPalindrome(s)<<endl;
    return 0;
}
