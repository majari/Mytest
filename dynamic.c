#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AGG_SUM 0
#define AGG_COUNT 1
#define AGG_MIN 2
#define AGG_MAX 3
#define AGG_AVG 4
int print_array(int *x[], int rows, int cols);

void group_by(int *data[], int rows, int cols, int gb_col, int agg_funcs[], 
              int agg_funcs_count, int agg_cols[], int agg_cols_count);

void emit_previous_row(int key, int agg_vals[], int agg_funcs_count);

void update_group(int key, int *row_data, int agg_cols[], int agg_vals[],
                  int agg_funcs[], int agg_funcs_count);
int main()
{
  int i,j, rows, cols,y;
  int gb_column;
  int agg_funcs[]={AGG_SUM,AGG_MAX,AGG_MIN, AGG_COUNT};
  int agg_cols[4];//aggregating sum(j), max(j)
   int **x = (int **)malloc(rows * sizeof(int *));
    for (i=0; i<rows; i++)
         x[i] = (int *)malloc(cols * sizeof(int));
 
  printf("Enter number of rows:");
	scanf("%d",&rows);

	printf("Enter number of columns:");
	scanf("%d",&cols);


	printf("Enter elements of the array:");
	for(i=0;i<rows;i++)
	for(j=0;j<cols;j++)
	{
		scanf("%d",&x[i][j]);
	}

	printf("Enter column for groupby query:");
	scanf("%d",&gb_column);


	printf("Enter cols to be aggregated:");
	for(i=0;i<4;i++)
	{
	scanf("%d",&agg_cols[i]);
	
	}

  print_array(x,rows,cols);
  //Trying to group by query
  //select i, sum(j), count(j) from t1;
  group_by(x, rows, cols, gb_column, agg_funcs, 4, agg_cols, 5);
}

int print_array(int *x[], int rows, int cols)
{
  int i, j;
  for(i=0;i<rows;i++)
  {
    for(j=0;j<cols;j++)
    {
      printf("%d ", x[i][j]);
    }
    printf("\n");
  }
}

void group_by(int *data[], int rows, int cols, int gb_col, int agg_funcs[], 
              int agg_funcs_count, int agg_cols[], int agg_cols_count)
{
  int i, j; //For iteration
  int key, prev_key=-1;
  int agg_vals[agg_funcs_count];
  printf("Entered group by with rows=%d cols=%d gb_col=%d func_count=%d cols_count=%d\n",
         rows, cols, gb_col, agg_funcs_count, agg_cols_count);
  memset(agg_vals, 0, agg_cols_count*sizeof(int));
  prev_key=data[0][gb_col];
  for(i=0;i<rows;i++)
  {
    key=data[i][gb_col];
    if(key != prev_key)
    {
      emit_previous_row(prev_key, agg_vals, agg_funcs_count);
      //initialise a set of counters
      memset(agg_vals, 0, agg_cols_count*sizeof(int));
    }
    update_group(key, data[i], agg_cols, agg_vals, agg_funcs, agg_funcs_count);
    prev_key=key;
  }
}

void emit_previous_row(int key, int agg_vals[], int agg_funcs_count)
{
  int i;
  printf("Emiting group\n");
  printf("Key=%d\n", key);
  for(i=0;i<agg_funcs_count;i++)
  {
    printf("Agg[%d]=%d\t",i,agg_vals[i]);
  }
  printf("\n");
}

void update_group(int key, int *row_data, int agg_cols[], int agg_vals[],
                  int agg_funcs[], int agg_funcs_count)
{
  int i;
  //printf("Entered update_group with key=%d\n", key);
  ///printf("CUrrent row values::\n");
  for(i=0;i<agg_funcs_count;i++)
  {
    switch(agg_funcs[i])
    {
      case AGG_AVG:
      case AGG_SUM:agg_vals[i]+=row_data[agg_cols[i]];
                   break;
      case AGG_MAX:if(row_data[agg_cols[i]] > agg_vals[i])
                   {
                     agg_vals[i]=row_data[agg_cols[i]];
                   }
                   break;
      case AGG_MIN:if(row_data[agg_cols[i]] < agg_vals[i])
                   {
                     agg_vals[i]=row_data[agg_cols[i]];
                   }
                   break;
      case AGG_COUNT:
                   agg_vals[i]++;
                   break;

    }
  }
}
