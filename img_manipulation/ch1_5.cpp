//
// image enhancement
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"

void gray_streching(unsigned char **ima, unsigned char **bima,int nr,int nc);



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
	gray_streching(ima,bima,nr,nc);
	Write_BMP_8bits("ex5_gray_streching.bmp", bima, nr, nc);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}

void gray_streching(unsigned char **ima, unsigned char **bima,int nr,int nc)
{
	for(int i=0;i<nr;i++){
		for(int j=0;j<nc;j++)
		{
			if(ima[i][j]<140) bima[i][j]=0;
			else if(ima[i][j]>203) bima[i][j]=255;
			else bima[i][j]=(ima[i][j]-140)*255/63;
		}
	}
}

