//
// image enhancement 
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
#include<fstream>
void binarize(unsigned char **ima, unsigned char **bima, int nr,int nc);

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
	binarize(ima,bima,nr,nc);
	Write_BMP_8bits("ex6_binarize.bmp", bima, nr, nc);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}

void binarize(unsigned char **ima, unsigned char **bima, int nr,int nc)
{
	ofstream out("ex6_histogram.txt");
	int histo[256]={0};
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			histo[ima[i][j]]++;
	for(int i=0;i<256;i++)
		out<<i<<"\t"<<histo[i]<<endl;
	
	
	for(int i=0;i<nr;i++)for(int j=0;j<nc;j++)
	{
		if(ima[i][j]<150)bima[i][j]=0;
		else bima[i][j]=255;
	}
}

