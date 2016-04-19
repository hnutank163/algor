#include <iostream>
#include <cmath>
using namespace std;

class Solution{
public:

    bool isPrime(int n){
        if( n%2==0 )
            return false;

        for(int i=3; ; i+=2){
            if(i > n/i )
                break;
            if( n%i == 0)
                return false;
        }

        return true;
    }

    int countPrimes(int n){
        int count = 1;
        if(n<=1)
            return 0;
        if(n==2)
            return 1;
        for(int i=3; i<n; ++i){
            if(isPrime(i))
                ++count;
        }
        return count;
    }

    int countPrimes2(int n){
        if( n<=2 )
            return 0;
        if( n == 3)
            return 1;
        int i=0;
        int j=0;
        bool *prime = new bool[n];
        for(; i<n; ++i){
            prime[i] = 1;
        }

        int count = n-2;
        for(j=2; j<sqrt(n); ++j)
        {
            if(prime[j]){
                for(i=j*j; i<n; i += j){
                    if(prime[i]){
                        prime[i] = 0;
                        --count;
                    }
                }
            }
        }

        delete [] prime;
        return count;
    }
};


int main(){
    Solution sl;
    cout<<sl.countPrimes2(10)<<" "<<sl.countPrimes2(20)<<" "
        <<sl.countPrimes2(1024)<<endl;
}
