//
// image enhancement 
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
#include <string>
void bit_planes(unsigned char **ima, unsigned char **bima, int nr,int nc,int shift);

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
	string name[8]={"ex7_bit-plane0.bmp","ex7_bit-plane1.bmp","ex7_bit-plane2.bmp","ex7_bit-plane3.bmp","ex7_bit-plane4.bmp","ex7_bit-plane5.bmp","ex7_bit-plane6.bmp","ex7_bit-plane7.bmp"};
	for(int shift=0;shift<8;shift++){
		bit_planes(ima,bima,nr,nc,shift);
		Write_BMP_8bits(name[shift].c_str(), bima, nr, nc);
	}	
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}

void bit_planes(unsigned char **ima, unsigned char **bima, int nr,int nc,int shift)
{
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			bima[i][j]=((ima[i][j]>>shift)%2)*255;
}

