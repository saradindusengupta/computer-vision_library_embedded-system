//
// image enhancement
// 2016.10.13 by Portran Lu
//
#include <iostream>
#include "stdlib.h"
#include "bmp.h"
#include<fstream>
using namespace std;
void excel(unsigned char **ima,int nc);


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
	excel(ima,nc);
	cout << "\nProgram done.\n";
	system("PAUSE");
	return 1;
}


void excel(unsigned char **ima,int nc)
{
	ofstream out("ex2_100row.xls");
	for(int j=0;j<nc;j++)
		out<<(int)ima[99][j]<<endl;
}



