#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


int rand_num(int limit)
{
	return((rand()%limit)+1);
}

void clear_arr(int a[])
{
	int i;
	for (i = 0; i < 9; i++)
	{
		a[i] = 0;
	}
}

void clear_mat(int a[][9])
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			a[i][j] = 0;
		}
	}
}

int run_arr(int a[],int num)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (a[num-1] > 0)
		{
			return(0);
		}
	}
	return(1);
}

int run_cube(int a[][9], int num,int i,int j)
{
	int lim_i = i + 3, lim_j = j + 3,row,col;

	for (row=i; row < lim_i; row++)
	{
		for (col=j; col < lim_j; col++)
		{
			if (a[row][col] == num)
			{
				return(0);
			}
		}
	}
	return(1);
}

int decide_i_j(int i)//for j as well
{
	int ret_i;
	if (i <= 2)
	{
		return(0);
	}
	else if (i > 2 && i <= 5)
	{
		return(3);
	}
	else
	{
		return(6);
	}
}

void print_mat(int a[][9])
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("[%d] ", a[i][j]);
			if ((j + 1) % 3 == 0&&j<8)
			{
				printf("||");
			}
		}
		if ((i + 1) % 3 == 0 && i < 8)
		{
			printf("\n---------------------------------------\n");
		}
		else
		{
			printf("\n\n");
		}
		
	}
}




int suduko(int mat[][9],int amount)
{
	int i, j,num,count_amount=0,count_trys=0,worked=1;
	int arr_row[9] = { 0 };//count numbers in rows

	//int arr_col[9] = { 0 };//count numbers in cols

	int mat_col[9][9];//counter number in cols



	clear_mat(mat_col);

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			
				num = rand_num(9);
				count_trys = 0;
				while (   (    !(run_arr(arr_row, num)) || !(run_arr(mat_col[j], num)) || !(run_cube(mat, num, decide_i_j(i), decide_i_j(j)))   ) && worked == 1)//checking if num was inserted already in row/col/cube
				{
					count_trys++;
					num = rand_num(9);
					if (count_trys > 100)
					{
						worked = 0;
					}
				}
				if (worked == 1)
				{
					mat[i][j] = num;
					arr_row[num - 1]++;
					mat_col[j][num - 1]++;
					count_amount++;
				}
				else
				{
					
					if (count_amount>amount)
					{
						printf("amount of inputs :%d\n", count_amount);
						print_mat(mat);
						printf("\n");
						return(count_amount);
					}
					
					return(amount);
				}
			
			

		}
		clear_arr(arr_row);
	}
	return(-1);
}

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
	{ }
}

void main()
{
	srand(time(0));
	int og_mat[9][9],ret,amount=0;
	clear_mat(og_mat);
	amount=suduko(og_mat,amount);
	while (amount != -1)
	{
		delay(1);
		srand(time(0));
		clear_mat(og_mat);
		amount = suduko(og_mat,amount);
	}
	printf("\n\nfull suduko at last \n ");
	print_mat(og_mat);


}
