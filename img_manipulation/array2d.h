//
// Dynamic 2D array memory allocation in C
// 2016.10.13 by Portran Lu
//

#include <stdlib.h>
#include <iostream> 
using namespace std;


unsigned char** UC2D(int nr, int nc)
{
	unsigned char** theArray;
	theArray = (unsigned char**) malloc(nr*sizeof(unsigned char*));  
	for (int i = 0; i < nr; i++)  
   	theArray[i] = (unsigned char*) malloc(nc*sizeof(unsigned char));  
   	return theArray;  
}

void freeUC2D(unsigned char** myArray, int nr) 
{
	for (int i = 0; i < nr; i++)free(myArray[i]);   
	free(myArray);  
}

int** INT2D(int nr, int nc) 
{  
	int** theArray;  
	theArray = (int**) malloc(nr*sizeof(int*));  
	for (int i = 0; i < nr; i++)  
   	theArray[i] = (int*) malloc(nc*sizeof(int));  
   	return theArray;  
}
void freeINT2D(int** myArray, int nr) 
{
	for (int i = 0; i < nr; i++)free(myArray[i]);   
	free(myArray);  
}


float** FLOAT2D(int nr, int nc) 
{  
	float** theArray;  
	theArray = (float**) malloc(nr*sizeof(float*));  
	for (int i = 0; i < nr; i++)  
   	theArray[i] = (float*) malloc(nc*sizeof(float));  
   	return theArray;  
}
void freeFLOAT2D(float** myArray, int nr) 
{
	for (int i = 0; i < nr; i++)free(myArray[i]);   
	free(myArray);  
}

/*
int main()
{
	int x;
	unsigned char** ima;
	int nr=3,nc=4;
	ima=UC2D(nr,nc);
	for(int i=0;i<nr;i++)for(int j=0;j<nc;j++)ima[i][j]=i*j;
	for(int i=0;i<nr;i++)
	{
		for(int j=0;j<nc;j++)cout<<int(ima[i][j])<<"\t";cout<<endl;
	}
	return 1;
}
*/
