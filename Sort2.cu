#include<thrust/sort.h>
#include<stdio.h>
#include<cuda.h>
#include<thrust/device_ptr.h>

int main()
{
   const int N = 6;
   int keys_h[N] = {  1,   2,   1,   2,   4,   1};
   int values_h[N] = {10,20,300,400,600,200};
   int *keys_d,*values_d; 
	
	size_t size = N * sizeof(int);
 
	cudaMalloc((void **) &keys_d, size);
	cudaMalloc((void **) &values_d, size);
	 
	cudaMemcpy(keys_d, keys_h, size, cudaMemcpyHostToDevice);
	cudaMemcpy(values_d, values_h, size, cudaMemcpyHostToDevice);

  	thrust::sort_by_key(keys_h, keys_h + N, values_h);
	
	cudaMemcpy(keys_d, keys_h, size, cudaMemcpyDeviceToHost);
	cudaMemcpy(values_d, values_h, size, cudaMemcpyDeviceToHost);

 	for(int i=0; i<N; i++)printf("%d %d \n",keys_h[i],values_h[i]);
	
        cudaFree(keys_d);
        cudaFree(values_d);
 
	 return 0;
}
