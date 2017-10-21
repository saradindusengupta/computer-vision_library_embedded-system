//
// image enhancement 
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
void down_sampling(unsigned char **ima, unsigned char **bima, int nr,int nc);

using namespace std;

int main(int argc, char** argv) {
	
	unsigned char **ima, **bima;
	int nr,nc; //image height and width
	char filename[128],temp;
	bool isfilefine = false;
    
    //read bmp image from file
    cout << "Enter input filename:";
	cin >> filename;
	isfilefine = Read_BMP(filename, ima, nr, nc);
	if (!isfilefine)	return 0;
	bima=UC2D(nr/4,nc/4);
	Write_BMP_8bits("ima.bmp", ima, nr, nc);
	
	down_sampling(ima,bima,nr/4,nc/4);
	Write_BMP_8bits("ex8_downsampling.bmp", bima, nr/4, nc/4);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}

void down_sampling(unsigned char **ima, unsigned char **bima, int nr,int nc)
{
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			bima[i][j]=ima[4*i][4*j];
}

