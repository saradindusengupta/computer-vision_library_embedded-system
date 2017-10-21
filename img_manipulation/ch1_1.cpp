//
// image enhancement
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
void horizontal(unsigned char **ima, unsigned char **bima, int nr,int nc);
void vertical(unsigned char **ima, unsigned char **bima, int nr,int nc);

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
	bima=UC2D(nr,nc);
	Write_BMP_8bits("ima.bmp", ima, nr, nc);
	horizontal(ima,bima,nr,nc);
	Write_BMP_8bits("ex1_horizontal.bmp", bima, nr, nc);
	vertical(ima,bima,nr,nc);
	Write_BMP_8bits("ex1_vertical.bmp", bima, nr, nc);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}


void horizontal(unsigned char **ima, unsigned char **bima, int nr,int nc)
{
	for(int i=0;i<nr;i++)
		for(int j=nc-1;j>=0;j--)
			bima[i][nc-1-j]=ima[i][j];
}

void vertical(unsigned char **ima, unsigned char **bima, int nr,int nc)
{
	for(int i=nr-1;i>=0;i--)
		for(int j=0;j<nc;j++)
			bima[nr-1-i][j]=ima[i][j];
}

