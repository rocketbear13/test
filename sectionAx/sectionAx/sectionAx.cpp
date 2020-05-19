// sectionAx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>
#include <stdio.h>

int main()
{
 omp_set_num_threads(4);
 double t1,t2,t3,t4;
 int A[10][10];
 int y1[10]={0},y2[10]={0},x[10] = {1,2,3,4,5,6,7,8,9,10};
 for(int i = 0; i < 10; i++)
	for(int j = 0; j < 10; j++)
		A[i][j] = (i+1)*(j+1);
 t1 = omp_get_wtime();
 for(int i = 0; i < 10; i++)
	for(int j = 0; j < 10; j++)
		y1[i] += A[i][j]*x[j];
 t2 = omp_get_wtime();
 printf("y1[9]=%d\n",y1[9]);
 printf("串行时间=%lf\n",t2-t1);

 t3 = omp_get_wtime();
 #pragma omp parallel sections
 {
	#pragma omp section
	{
		#pragma omp task
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 10; j++)
				y2[i] += A[i][j]*x[j];

		#pragma omp task
		for(int i = 3; i < 6; i++)
			for(int j = 0; j < 10; j++)
				y2[i] += A[i][j]*x[j];

		#pragma omp task
		for(int i = 6; i < 8; i++)
			for(int j = 0; j < 10; j++)
				y2[i] += A[i][j]*x[j];

		#pragma omp task
		for(int i = 8; i < 10; i++)
			for(int j = 0; j < 10; j++)
				y2[i] += A[i][j]*x[j];
	}
 }
 t4 = omp_get_wtime();
 printf("y2[9]=%d\n",y2[9]);
 printf("并行时间=%lf\n",t4-t3);
 return 0;
}

