#include<stdio.h>
#include<stdlib.h>
#define AGG_SUM 0
#define AGG_MIN 1
#define AGG_MAX 2

int *data,*agg_funcs,*agg_cols;

void group_by(int rows,int cols,int gb_col,int agg_funcs_count,int agg_cols_count); // Group by queries using Aggregate functions

int main()
{
	int i,j,rows,cols,gb_col,agg_funcs_count,agg_cols_count,x,y;

     //Dynamic Memory Allocation of Arrays
	data = (int*)malloc(rows*cols*sizeof(int));
	agg_funcs = (int*)malloc(cols*sizeof(int));
	agg_cols = (int*)malloc(cols*sizeof(int));


	printf("Enter number of rows:");
	scanf("%d",&rows);

	printf("Enter number of columns:");
	scanf("%d",&cols);


	printf("Enter elements of the array:");
	for(i=0;i<rows;i++)
	for(j=0;j<cols;j++)
	{
		scanf("%d",&x);
		*(data+i*cols+j)=x;
	}

	printf("Enter column for groupby query:");
	scanf("%d",&gb_col);

	printf("Enter number of cols to be aggregated:");
	scanf("%d",&agg_cols_count);


	printf("Enter cols to be aggregated:");
	for(i=0;i<agg_cols_count;i++)
	{
	scanf("%d",&x);
	*(agg_cols+i)=x;
	}
	printf("Enter the number of funcs to be implemented:");
	scanf("%d",&agg_funcs_count);

	printf("Enter the agg funcs to be used:");
	printf("\n Enter 0 : Sum \n 1 : Minimum \n 2 : Maximum \n");
	for(i=0;i<agg_funcs_count;i++)
	{
		scanf("%d",&x);
		*(agg_funcs+i)=x;
	}
	group_by(rows,cols,gb_col, agg_funcs_count, agg_cols_count);

	return 0;

}

void group_by(int rows,int cols,int gb_col,int agg_funcs_count,int agg_cols_count)
{
	int i,p,j,c,k=0,l, data_output[10][10];
	for(p=0;p<agg_funcs_count;p++)
	{
		for(i=0; i<rows; i++)
		for(j=0; j<cols; j++)
			data_output[i][j] = *(data+i*cols+j); // Maintaining Copy of Data  
             
		switch (agg_funcs[p])
		{
			case AGG_SUM:
			for(i=0; i<rows; i++)
			{
				for(j=i+1; j<rows; j++)
				{
					if(data_output[i][gb_col] == data_output[j][gb_col])
					{
						data_output[i][agg_cols[k]] = data_output[i][agg_cols[k]]+ data_output[j][agg_cols[k]];
						
					    for(l=0; l<cols; l++)
					    {
						data_output[j][l]=0;
					    }
					}
				}
			}
               
               k++;
			
			break;

			case AGG_MIN:
				for(i=0; i<rows; i++)
				{
					for(j=i+1; j<rows; j++)
					{
					if(data_output[i][gb_col]==data_output[j][gb_col])
					{

						if(data_output[j][agg_cols[k]]<=data_output[i][agg_cols[k]])
     					data_output[i][agg_cols[k]]=data_output[j][agg_cols[k]];

     					for(l=0;l<cols;l++)
     	     				data_output[j][l]=0;
					}
				}
			}
			k++;
			break;

			case AGG_MAX:

			for(i=0; i<rows; i++)
				{
					for(j=i+1; j<rows; j++)
					{
     					if(data_output[i][gb_col]==data_output[j][gb_col])
     					{
							if(data_output[j][agg_cols[k]]>data_output[i][agg_cols[k]])
							data_output[i][agg_cols[k]]=data_output[j][agg_cols[k]];

     						for(l=0;l<cols;l++)
          						data_output[j][l]=0;
     					}
     				}
     			}
			k++;
			break;

		}
          // Display Output of Group by Function

    		c=1;
     	printf("Result of group_by function: \n");
		 
		for(i=0;i<rows;i++)
		{
			for(j=0;j<cols;j++)
			{
				if(data_output[i][j]==0)
				{
					c=0;
				}
				else
				{
					c=1;
					break;
				}
			}
			if(c == 1)
		     {       
			       
				for(j=0;j<cols;j++)
				{
					printf("%d ",data_output[i][j]);
				}
				printf("\n");
			}
		}
	}

}
