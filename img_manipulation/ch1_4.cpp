//
// image enhancement 
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
#include<fstream>
void upper_left_excel(unsigned char **ima, unsigned char **bima);

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
	upper_left_excel(ima,bima);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}

void upper_left_excel(unsigned char **ima, unsigned char **bima)
{
	ofstream out("ex4_8x8pixels.xls");
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
		{
            out<<(int)ima[i][j]<<"\t";
		}
		out<<endl;
	}
}

