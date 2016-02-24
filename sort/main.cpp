#include <iostream>
#include "sort.hpp"


int main(int argc, char *argv[])
{
   int a[] = {3,2,1,4,6,5,7,9,8,5};
   insert_sort(a,a+ sizeof(a)/sizeof(int));
   print(a, a+sizeof(a)/sizeof(int));
    return 0;
}
