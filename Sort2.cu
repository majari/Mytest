#include <thrust/sort.h>
#include<stdio.h>

int main()
{
  const int N = 6;
  int    keys[N] = {  1,   2,   1,   2,   4,   1};
  int values[N] = {10,20,300,400,600,200};

  thrust::sort_by_key(keys, keys + N, values);

 for(int i=0; i<N; i++)printf("%d %d \n",keys[i],values[i]);

return 0;
}
