#include<stdio.h>
#include<iostream>
#include<cuda.h>
#include<thrust/sort.h>
#include<thrust/device_ptr.h>

int main(void)
{
	int *a_h,*a_d;
	const int N=10;
	size_t size = N*sizeof(int);
	a_h = (int*)malloc(size);
	cudaMalloc((void**) &a_d ,size);
	std::cout<<"enter 10 numbers";

	for(int i =0; i<N; i++)
	{
		std::cin>>a_h[i];
	}
	for(int i =0; i<N; i++)
	{ 
		
		printf("%d %d\n", i, a_h[i]);
	}
	cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
	thrust::device_ptr<int> t_a(a_d);
	thrust::sort(t_a, t_a + N);

	cudaMemcpy(a_h, a_d, sizeof(int)*N,cudaMemcpyDeviceToHost);
	
	printf("Sorted list is:\n");
	
	for(int i=0; i<N; i++)
	{ 
		
		printf("%d %d\n", i, a_h[i]);
	}

	free(a_h); cudaFree(a_d);
	
	return 0;
}
