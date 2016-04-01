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

void SORT::max_heap(int *a, int i, int n) {
    int j, temp;
    temp = a[i];
    j = 2*i;
    while (j <= n)
    {
        if (j < n && a[j+1] > a[j])
            j = j+1;
        if (temp > a[j])
            break;
        else if (temp <= a[j])
        {
            a[j/2] = a[j];
            j = 2*j;
        }
    }
    a[j/2] = temp;
    return;
}

void SORT::heapsort(int *a, int n) {
    int i, temp;
    for (i = n; i >= 2; i--) {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        max_heap(a, 1, i - 1);
    }
}

void SORT::build_maxheap(int *a, int n) {
    int i;
    for (i = n / 2; i >= 1; i--) {
        max_heap(a, i, n);
    }
}

