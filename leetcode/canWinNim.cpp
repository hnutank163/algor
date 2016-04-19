#include <iostream>
using namespace std;

//there are n stones , you pick first(you can pick 1~3 a time),
//another one is smart enough, give you n, can you win?
class Solution{
public:
    bool canWinNim(int n){
        if(n <= 3)
            return true;
        else{
            return !(canWinNim(n-1) && canWinNim(n-2) && canWinNim(n-3));
        }
    }

    //math solution
    bool canWinNim2(int n){
        return n%4; // return n&3;
    }
};


int main(){
    Solution sl;
    cout<<sl.canWinNim(3)<<" "<<sl.canWinNim(4)<<" "<<sl.canWinNim(6)<<" "
        <<sl.canWinNim(8)<<" "<<sl.canWinNim(16)<<" "<<sl.canWinNim(17)<<endl;
    return 0;
}
