//
// Program: Bitmap functions
// This program contains functions to read and write graphic bitmap data.
// The functions are capable of only handling uncompressed 24 bit images.
//

#ifndef _BMP_H_
#define _BMP_H_

#include <iostream>
#include <fstream>
#include "array2d.h"

using namespace std;

// standard bitmap header information
struct bmp_h
{
	//char c1;
	//char c2;
	unsigned int fs;		// file size in bytes, dword (4 bytes)
	unsigned int res;		// reserved for later use
	unsigned int bdo;		// Bitmap Data Offset, beginning of data
	unsigned int bhs;		// Bitmap Header Size, size of bmp info
	unsigned int width;		// horizontal width in pixels
	unsigned int height;	// vertical height in pixels
	short int planes;		// number of planes in bitmap
	short int bits;			// bits per pixel
	unsigned int comp;		// compression mode
	unsigned int bds;		// Bitmap Data Size, size of data
	unsigned int hr;		// horizontal resolution, pixels per meter
	unsigned int vr;		// vertical resolution
	unsigned int colors;	// number of colors used
	unsigned int imp_colors;// important colors
};

bool Read_BMP(const char *filename,unsigned char** &ima,int &nr,int &nc)
{
    bool ok = true;         // assume file is handlable
    int row, col, padding;
    char temp;
    bmp_h header;
    ifstream file;
    
    unsigned char R, G, B;
    
    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }
	
    // bitmap must be 24 bit, uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }   
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    } 
    
    if (ok)
	{
        nr = header.height;
        nc = header.width;
        ima = UC2D(header.height, header.width);
        // move offset to rgb_raw_data_offset to get RGB raw data
        
        
        // row data is saved to nearest multiple of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
		
		
        file.seekg(header.bdo);
        if(header.bits == 32)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B = temp;
                file.read ((char *)&temp, sizeof(temp));
                G = temp;
                file.read ((char *)&temp, sizeof(temp));
                R = temp;
                file.read ((char *)&temp, sizeof(temp));
                ima[row][col] =0.3*R+0.59*G+0.11*B;
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 24)
        {

          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B = temp;
                file.read ((char *)&temp, sizeof(temp));
                G = temp;
                file.read ((char *)&temp, sizeof(temp));
                R = temp;
                ima[row][col] =0.3*R+0.59*G+0.11*B;
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 8)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                ima[row][col] = temp;
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
    }
    return (ok);
}
bool Read_BMP(const char *filename,unsigned char** &R,unsigned char** &G,unsigned char** &B,unsigned char** &Y,int &nr,int &nc)
{
    bool ok = true;         // assume file is handlable
    int row, col, padding;
    char temp;
    bmp_h header;   
    ifstream file;

    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }

    // bitmap must be uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }   
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    }

    
    if (ok)
    {
        nr=header.height;
        nc=header.width;
        R = UC2D(header.height, header.width);
        G = UC2D(header.height, header.width);
        B = UC2D(header.height, header.width);
        Y = UC2D(header.height, header.width);
         // move offset to rgb_raw_data_offset to get RGB raw data
        file.seekg(header.bdo);
        
        // row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
        
        if(header.bits == 32)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                R[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 24)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                R[row][col] = temp;
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 8)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                Y[row][col] = temp;
                R[row][col] = Y[row][col];
                G[row][col] = Y[row][col];
                B[row][col] = Y[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }         
        }       
    }
    return (ok);
}
// file should be open in binary mode
//
//bool __fastcall TForm1::Write_BMP(ofstream &file, bmp_h header, unsigned char** r, unsigned char** g, unsigned char** b)
bool  Write_BMP_8bits(const char *filename,unsigned char** ima,int nr,int nc)
{
    bool ok = true;         // for checking file output problems
    char i = 'B', d = 'M';
    int row, col, padding;
    char temp;
    bmp_h header;
    int byte_per_pixel=1;
    unsigned char Palette[256*4];
    int nbpal;
    ofstream file;

    file.open(filename, ios::binary);

    ok=file.is_open();
    if( !ok )
    {
        cout << "File Problems.\n";
        return ok;
    }
          
    //raw data offset
    header.bdo=1078;  
    header.bhs=40;
    header.height=nr;
    header.width=nc;
    header.planes=1;
    header.bits=8;
    header.comp=0;
    header.bds=0;
    header.hr=0;
    header.vr=0;
    header.colors=0;
    header.imp_colors=0;

    // file size
    header.fs = nr * nc * byte_per_pixel + header.bdo;
    header.res=0;
    // BM id header
    ok = file.write ((char *)&i, sizeof(i));
    ok = file.write ((char *)&d, sizeof(d));

    // rest of header
    ok = file.write ((char *)&header, sizeof(header));
    
    //Palette
    for(nbpal=0;nbpal<256;nbpal++)
    {
      Palette[4*nbpal+0]=nbpal;
      Palette[4*nbpal+1]=nbpal;
      Palette[4*nbpal+2]=nbpal;
      Palette[4*nbpal+3]=0;
    }
    //fwrite(Palette, sizeof(unsigned char), 256*4, fp_t);
    ok = file.write ((char *)&Palette, sizeof(Palette));
    
    // write image
    if (ok)
    {
    	// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
    	
        // data stored bottom up, left to right
        for (row=header.height-1; row>=0; row--)
        {
            for (col=0; col<header.width; col++)
            {
                temp = ima[row][col];
                file.write ((char *)&temp, sizeof(temp));
            }
            for (col=0; col<padding; col++)
			{
				file.write ((char *)&temp, sizeof(temp));
			}
        }
    }
    return (ok);

}
//---------------------------------------------------------------------------
bool  Write_BMP_24bits(const char *filename,unsigned char** R,unsigned char** G,unsigned char** B,int nr,int nc)
{
    bool ok = true;         // for checking file output problems
    char i = 'B', d = 'M';
    int row, col, padding;
    char temp;
    bmp_h header;
    int byte_per_pixel=1;
    unsigned char Palette[256*4];
    int nbpal;
    ofstream file;

    file.open(filename, ios::binary);

    ok=file.is_open();
    if( !ok )
    {
        cout << "File Problems.\n";
        return ok;
    }
          
    //raw data offset
    header.bdo=54;
    header.bhs=40;
    header.height=nr;
    header.width=nc;
    header.planes=1;
    header.bits=24;
    header.comp=0;
    header.bds=0;
    header.hr=0;
    header.vr=0;
    header.colors=0;
    header.imp_colors=0;

    // file size
    header.fs = nr * nc * byte_per_pixel + header.bdo;
    header.res=0;
    // BM id header
    ok = file.write ((char *)&i, sizeof(i));
    ok = file.write ((char *)&d, sizeof(d));

    // rest of header
    ok = file.write ((char *)&header, sizeof(header));

    // write image
    if (ok)
    {
    	// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
    	
        // data stored bottom up, left to right
        for (row=header.height-1; row>=0; row--)
        {
            for (col=0; col<header.width; col++)
            {
                temp = B[row][col];
                file.write ((char *)&temp, sizeof(temp));
                temp = G[row][col];
                file.write ((char *)&temp, sizeof(temp));
                temp = R[row][col];
                file.write ((char *)&temp, sizeof(temp)); 
            }
            for (col=0; col<padding; col++)
			{
				file.write ((char *)&temp, sizeof(temp));
			}
        }
    }
    return (ok);

}

//---------------------------------------------------------------------------



//
// Function: Print_BMP_Header
// Display Bitmap header info to console
//
void Print_BMP_Header (bmp_h h)
{
	cout << endl;  
	//cout << "Char 1             = " << h.c1 << endl;
	//cout << "Char 2             = " << h.c2 << endl;
	cout << "File Size          = " << h.fs << endl;
	cout << "Width              = " << h.width << endl;
	cout << "Height             = " << h.height << endl;
	cout << "Bits per Pixel     = " << h.bits << endl;
	cout << "Compression        = " << h.comp << endl;
}


#endif
