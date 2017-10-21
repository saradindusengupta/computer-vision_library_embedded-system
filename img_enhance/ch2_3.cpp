//
// Statistical Histogram Equalization
// 2016.10.13 by Portran Lu
//

#include <iostream>
#include <math.h>
#include "stdlib.h"
#include "bmp.h"
void mean_stddev(unsigned char **ima, float &mean, float &std_dev, int nr, int nc);

int main(int argc, char** argv) {

	unsigned char **ima, **ahima, **window;
	int nr,nc; //image height and width
	char filename[128], c;
	bool isfilefine = false;

    //read bmp image from file
    cout << "Enter input filename:";
	cin >> filename;
	isfilefine = Read_BMP(filename, ima, nr, nc);
	if (!isfilefine)	return 0;
	ahima=UC2D(nr,nc);
	Write_BMP_8bits("ima.bmp", ima, nr, nc);
	
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			ahima[i][j]=ima[i][j];

	int winsize=21, hsize=winsize/2;
	window=UC2D(winsize,winsize);
	float globalmean=0, mean=0.0;
	float std_dev=0.0;
	float k1=0.0, k2=0.0;
	cout<<"input k1= ";
	cin>>k1;
	cout<<"input k2= ";
	cin>>k2;
	globalmean=0;
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			globalmean+=ima[i][j];
	globalmean=globalmean/(nr*nr);
	int t;
	for(int i=hsize;i<(nr-hsize);i++)
		for(int j=hsize;j<(nc-hsize);j++)
		{
			for(int ii=-hsize;ii<=hsize;ii++)
				for(int jj=-hsize;jj<=hsize;jj++)
					window[ii+hsize][jj+hsize]=ima[i+ii][j+jj];
			mean_stddev(window, mean, std_dev, winsize, winsize);
			t=(k1*(globalmean/std_dev)*(ima[i][j]-mean))+(k2*mean);
			if(t>255)
				ahima[i][j]=255;
			else
				ahima[i][j]=t;
		}
	Write_BMP_8bits("AHE.bmp", ahima, nr, nc);
	
	cout << "\nProgram done.\n";
	return 1;
}

void mean_stddev(unsigned char **ima, float &mean, float &std_dev, int nr, int nc)
{
	long N, sum=0;
	N=(long)nr*(long)nc;
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
			sum+=ima[i][j];

	mean=(float)sum/(float)N; //Calculating the mean
	
	float sumdev=0.0;
	float d=0.0;
	for(int i=0;i<nr;i++)
		for(int j=0;j<nc;j++)
		{
			d=ima[i][j]-mean;
			sumdev=sumdev+d*d;
		}
	std_dev=sqrt(sumdev/N); //Calculating the standard deviance
}
