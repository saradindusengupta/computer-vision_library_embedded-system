#include <iostream>
#include "stdlib.h"
#include "bmp.h"

//
// Histogram Equalization
// 2016.10.13 by Portran Lu
//
void HistogramEqualization(unsigned char **ima, unsigned char **bima, int nr,int nc);

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
	HistogramEqualization(ima,bima,nr,nc);
	Write_BMP_8bits("ex1_HE.bmp", bima, nr, nc);
	cout << "\nProgram done.\n";
	return 1;
}

void HistogramEqualization(unsigned char **ima, unsigned char **bima, int nr,int nc)
{
	long ImaSize=nr*nc;
    int histo[256];  //histogram
    float accpbhisto[256]; // cumulative istogram
    int table[256];// Look-up table for mapping fuction of histogram equalization
 // Initialize
    for(int i=0;i<256;i++)
    {
      histo[i]=0;
      table[i]=0;
      accpbhisto[i]=0.0;
    }
 // Compute histogram
    for(int i=0;i<nr;i++)for(int j=0;j<nc;j++)histo[ima[i][j]]++;

 // Compute cumulative histogram
    accpbhisto[0]=float(histo[0])/float(ImaSize);
    for(int i=1;i<256;i++)
      accpbhisto[i]=accpbhisto[i-1]+float(histo[i])/float(ImaSize);

// compute mapping function
	for(int i=0;i<256;i++)table[i]=char(accpbhisto[i]*256.);

// Enhancement
	for(int i=0;i<nr;i++)for(int j=0;j<nc;j++)
  		bima[i][j]=table[ima[i][j]];
}

