#include<stdio.h>
void group_by(int rows,int cols,int data[50][50],int gb_col,int agg_funcs[5],int agg_funcs_count, int agg_cols[20],int agg_cols_count);
int main()
{
	int data[50][50];
	int i,j,rows,cols,gb_col,agg_funcs_count,agg_cols[50],agg_cols_count;
	int agg_funcs[5];
	clrscr();

	printf("Enter number of rows");
	scanf("%d",&rows);

	printf("Enter number of columns");
	scanf("%d",&cols);

	printf("Enter elements of the array");
	for(i=0;i<rows;i++)
	for(j=0;j<cols;j++)
	{
		scanf("%d",&data[i][j]);
	       //	data_output[i][j]=data[i][j];
	}
	printf("Enter column for groupby query");
	scanf("%d",&gb_col);

	printf("Enter number of cols to be aggregated");
	scanf("%d",&agg_cols_count);

	printf("Enter cols to be aggregated");
	for(i=0;i<agg_cols_count;i++)
	scanf("%d",&agg_cols[i]);

	printf("Enter the number of funcs to be implemented");
	scanf("%d",&agg_funcs_count);

	printf("Enter the agg funcs to be used");
	for(i=0;i<agg_funcs_count;i++)
	{
		scanf("%d",&agg_funcs[i]);
	}
	//printf(" gb_Col: %d",gb_col);
	group_by(rows,cols,data,gb_col, agg_funcs, agg_funcs_count,  agg_cols,agg_cols_count);

	getch();
	return 0;

}
void group_by(int rows,int cols,int data[50][50],int gb_col,int agg_funcs[5],int agg_funcs_count, int agg_cols[20],int agg_cols_count)
{
	int i,p,j,c,k,l, data_output[50][50];
	for(p=0;p<agg_funcs_count;p++)
	{
		int count= 0;
		for(i=0; i<rows; i++)
		for(j=0; j<cols; j++)
			data_output[i][j] = data[i][j];
		switch (agg_funcs[p])
		{
			case 1:
			for(i=0; i<rows; i++)
			{
				for(j=i+1; j<rows; j++)
				{

					 if(data_output[i][gb_col] == data_output[j][gb_col])
					 {
					     count++;
					     // printf("Data: %d",data_output[j][gb_col]);
					     //printf("C: %d",count);
					     for(k=0; k<agg_cols_count; k++)
					     {
						data_output[i][agg_cols[k]]=data_output[i][agg_cols[k]]+data_output[j][agg_cols[k]];
					       //	printf("D: %d ",data_output[i][agg_cols[k]]);
					     }
					     for(l=0; l<cols; l++)
					     {
						data_output[j][l]=0;
					     }
					 }
				}
			}

			break;

			case 2:
				for(i=0; i<rows; i++)
				{
					for(j=i+1; j<rows; j++)
					{
					 if(data_output[i][gb_col]==data_output[j][gb_col])
					{
					  count++;
					  for(k=0;k<agg_cols_count;k++)
					{
						if(data_output[j][agg_cols[k]]<=data_output[i][agg_cols[k]])
						data_output[i][agg_cols[k]]=data_output[j][agg_cols[k]];
					}
					for(l=0;l<cols;l++)
					data_output[j][l]=0;
					}
				}
			}
			break;

			case 3:
			for(i=0; i<rows; i++)
				{
					for(j=i+1; j<rows; j++)
					{
					 if(data_output[i][gb_col]==data_output[j][gb_col])
					{
					  count++;
					  for(k=0;k<agg_cols_count;k++)
					{
						if(data_output[j][agg_cols[k]]>data_output[i][agg_cols[k]])
						data_output[i][agg_cols[k]]=data_output[j][agg_cols[k]];
					}
					for(l=0;l<cols;l++)
					data_output[j][l]=0;
					}
				}
			}
			break;

		}
		c=1;
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
					printf("%d",data_output[i][j]);
				}
				printf("\n");
			}
		}
	}

}
