//
// Local Histogram Equalization
// 2016.10.13 by Portran Lu
//

#include <iostream>
#include <string>
#include "stdlib.h"
#include "bmp.h"

void LocalHE(unsigned char **ima, unsigned char **lhima, int blocksize, int nr, int nc);

int main(int argc, char** argv) {

	unsigned char **ima, **lhima;
	int nr,nc; //image height and width
	int blocksize;
	char filename[128], c;
	bool isfilefine = false;

    //read bmp image from file
    cout << "Enter input filename:";
	cin >> filename;
	isfilefine = Read_BMP(filename, ima, nr, nc);
	if (!isfilefine)	return 0;
	lhima=UC2D(nr,nc);
	Write_BMP_8bits("ima.bmp", ima, nr, nc);
	cout << "Enter blocksize:";
	cin >> blocksize;
	LocalHE(ima, lhima, blocksize, nr, nc);
	Write_BMP_8bits("ex2_LocalHE.bmp", lhima, nr, nc);
	
	cout << "\nProgram done.\n";
	return 1;
}

void LocalHE(unsigned char **ima, unsigned char **lhima, int blocksize, int nr, int nc)
{
	int hsize, rank;
	if(blocksize%2==0)
		blocksize+=1;
	hsize=blocksize/2;
	int area=blocksize*blocksize;
	for(int i=hsize;i<(nr-hsize);i++)
		for(int j=hsize;j<(nc-hsize);j++)
		{
			rank=0;
			for(int k=(i-hsize);k<=(i+hsize);k++)
				for(int l=(j-hsize);l<=(j+hsize);l++)
					if(ima[i][j]>ima[k][l])
						rank++;
			lhima[i][j]=rank*255/area;
		}
}
