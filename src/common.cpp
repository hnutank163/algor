#include "common.h"

int max_nums_1(const int *a, int n)
{
    int i, j, k;
    int max = 0;
    for (i = 0; i < n; ++i) {
        for (j = i; j < n; ++j) {
            int sum = 0;
            for (k = i; k <=j; ++k) {
               sum += a[k] ;
            }
            if( max < sum )
                max = sum;
        }
    }
    
    return max;
}

int max_nums_2(const int *a, int n)
{
    int i, j;
    int max = 0;
    
    for (i = 0; i < n; ++i) {
        int sum = 0;
        for(j=i; j<n; ++j)
        {
            sum += a[j];
            if(max < sum)
                max = sum;
        }
    }

    return max;
}
