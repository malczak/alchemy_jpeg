/*
	segfaultlabs.com
 */
#include <AS3.h>
#include <math.h>
#include <stdio.h>

typedef struct bitstring__ {
	int len;
	int val;
} bitstring;

// constants 

unsigned char std_dc_luminance_nrcodes[] = { 0, 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
unsigned char std_dc_luminance_values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

unsigned char std_dc_chrominance_nrcodes[] = { 0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
unsigned char std_dc_chrominance_values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

unsigned char std_ac_luminance_nrcodes[] = { 0, 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7D };
unsigned char std_ac_luminance_values[] = {  0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
											0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
											0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08,
											0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0,
											0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16,
											0x17, 0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28,
											0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
											0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
											0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
											0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
											0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
											0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
											0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
											0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
											0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,
											0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5,
											0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4,
											0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE1, 0xE2,
											0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA,
											0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
											0xF9, 0xFA };

unsigned char std_ac_chrominance_nrcodes[] = { 0, 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 0x77 };
unsigned char std_ac_chrominance_values[] = {0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21,
											0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
											0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
											0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0,
											0x15, 0x62, 0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34,
											0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26,
											0x27, 0x28, 0x29, 0x2A, 0x35, 0x36, 0x37, 0x38,
											0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
											0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
											0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
											0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
											0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
											0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96,
											0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5,
											0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4,
											0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3,
											0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2,
											0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA,
											0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9,
											0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
											0xF9, 0xFA };

unsigned char ZigZag[] = { 0,  1,  5,  6, 14, 15, 27, 28,
						  2,  4,  7, 13, 16, 26, 29, 42,
						  3,  8, 12, 17, 25, 30, 41, 43,
						  9, 11, 18, 24, 31, 40, 44, 53,
						  10, 19, 23, 32, 39, 45, 52, 54,
						  20, 22, 33, 38, 46, 51, 55, 60,
						  21, 34, 37, 47, 50, 56, 59, 61,
						  35, 36, 48, 49, 57, 58, 62, 63 };

// static length arrays
   /**
	 *  @private
	 *  Initialized by initCategoryNumber() in constructor.
	 */
int category[65535];

    /**
	 *  @private
	 *  Initialized by initCategoryNumber() in constructor.
	 */
bitstring bitcode[65535];
    
    /**
	 *  @private
	 *  Initialized by initQuantTables() in constructor.
	 */
double YTable[64];

    /**
	 *  @private
	 *  Initialized by initQuantTables() in constructor.
	 */
double UVTable[64];

    /**
	 *  @private
	 *  Initialized by initQuantTables() in constructor.
	 */
double fdtbl_Y[64];

    /**
	 *  @private
	 *  Initialized by initQuantTables() in constructor.
	 */
double fdtbl_UV[64];


/**
 *  @private
 */
double DU[64];

/**
 *  @private
 */
double YDU[64];

/**
 *  @private
 */
double UDU[64];

/**
 *  @private
 */
double VDU[64];


double aasf[] = { 1.0, 1.387039845, 1.306562965, 1.175875602,
				 1.0, 0.785694958, 0.541196100, 0.275899379 };
	
short YQT[] = {	16, 11, 10, 16, 24, 40, 51, 61,
				12, 12, 14, 19, 26, 58, 60, 55,
				14, 13, 16, 24, 40, 57, 69, 56,
				14, 17, 22, 29, 51, 87, 80, 62,
				18, 22, 37, 56, 68,109,103, 77,
				24, 35, 55, 64, 81,104,113, 92,
				49, 64, 78, 87,103,121,120,101,
				72, 92, 95, 98,112,100,103, 99 };

short UVQT[] = { 17, 18, 24, 47, 99, 99, 99, 99,
				18, 21, 26, 66, 99, 99, 99, 99,
				24, 26, 56, 99, 99, 99, 99, 99,
				47, 66, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99,
				99, 99, 99, 99, 99, 99, 99, 99 };

// Huffman tables
int initialized;
bitstring* YDC_HT;
bitstring* UVDC_HT;
bitstring* YAC_HT;
bitstring* UVAC_HT;


#ifdef LOGSON

#define _Tn( msg )  sprintf( fmsg, "%s [%d] : %s", __FILE__, __LINE__, msg ); sztrace( fmsg );
#define _T( msg ) char fmsg[200]; _Tn( msg );

#else

#define _Tn( msg ) 
#define _T( msg ) 

#endif

#ifdef FILE_BA

typedef FILE* OUTPUT;

/* this approach is almost x4 faster than using AS3_ByteArray_* methods with AS3_Val object */

/* read, write, seek, close a File inside Alchemy, File = ByteArray */
static int readba(void *cookie, char *dst, int size)
{
	return AS3_ByteArray_readBytes(dst, (AS3_Val)cookie, size);
}

static int writeba(void *cookie, const char *src, int size)
{
	return AS3_ByteArray_writeBytes((AS3_Val)cookie, (char *)src, size);
}

static fpos_t seekba(void *cookie, fpos_t offs, int whence)
{
	return AS3_ByteArray_seek((AS3_Val)cookie, offs, whence);
}

static int closeba(void *cookie)
{
	AS3_Val zero = AS3_Int(0);
	AS3_SetS((AS3_Val)cookie, "position", zero);
	AS3_Release(zero);
	return 0;
}

	#define write( v, size, output ) fwrite( (v), (size), 1, (output) );

#else
	/* this approach is much slower, almost ~4times slower */
	typedef AS3_Val OUTPUT;

	#define write( v, size, output ) AS3_ByteArray_writeBytes( (AS3_Val)(output), (v), (size) );

#endif

#define IOVAR char iudum;

#define writeByte( v ) iudum = v; \
					   write( (void*)&iudum, sizeof(char),  output );

#define writeWord( v ) writeByte( (v>>8)&0xff ); \
					   writeByte( v&0xff ); \


inline void writeBits( OUTPUT output, int* bytenew, int* bytepos, bitstring bs )
{
	_T("writeBits");

	IOVAR;
	unsigned int value = bs.val;
	int posval = bs.len - 1;
	
	while (posval >= 0)
	{
		if (value & (int)(1 << posval) )
		{
			*bytenew |= (int)(1 << *bytepos);
		}
		posval-=1;
		*bytepos-=1;
		if (*bytepos < 0)
		{
			if (*bytenew == 0xFF)
			{
				writeByte(0xFF);
				writeByte(0);
			}
			else
			{
				writeByte(*bytenew);
			}
			*bytepos = 7;
			*bytenew = 0;
		}
	}
}


// Huffman tables routines

void computeHuffmanTbl( unsigned char *nrcodes, unsigned char *std_table, bitstring** out )
{
	_T("computeHuffmanTbl");

	int codevalue = 0;
	int pos_in_table = 0;
	
	(*out) = (bitstring*)malloc( sizeof(bitstring)*251 );
	
	unsigned char k;
	int j;
	
	for ( k=1; k<=16; ++k)
	{
		for ( j=1; j<=nrcodes[k]; ++j )
		{
			(*out)[std_table[pos_in_table]].val = codevalue;
			(*out)[std_table[pos_in_table]].len = k;
			pos_in_table+=1;
			codevalue+=1;
		}
		codevalue <<= 1;
	}
}

void initHuffmanTbl()
{
	_T("initHuffmanTbl");

	computeHuffmanTbl( std_dc_luminance_nrcodes, std_dc_luminance_values, (bitstring**)&YDC_HT );
	computeHuffmanTbl( std_dc_chrominance_nrcodes, std_dc_chrominance_values, (bitstring**)&UVDC_HT );
	computeHuffmanTbl( std_ac_luminance_nrcodes, std_ac_luminance_values, (bitstring**)&YAC_HT );
	computeHuffmanTbl( std_ac_chrominance_nrcodes, std_ac_chrominance_values, (bitstring**)&UVAC_HT );
}

void initCategoryNumber()
{
	_T("initCategoryNumber");

	int nrlower = 1;
	int nrupper = 2;
	int cat, nr, nrneg;
	for ( cat=1; cat<=15; cat++)
	{
		//Positive numbers
		for ( nr=nrlower; nr<nrupper; nr++)
		{
			category[32767+nr] = cat;
			bitcode[32767+nr].len = cat;
			bitcode[32767+nr].val = nr;
		}
		//Negative numbers
		for ( nrneg=-(nrupper-1); nrneg<=-nrlower; nrneg++)
		{
			category[32767+nrneg] = cat;
			bitcode[32767+nrneg].len = cat;
			bitcode[32767+nrneg].val = nrupper-1+nrneg;
		}
		nrlower <<= 1;
		nrupper <<= 1;
	}
}

void initQuantTables( int sf )
{
	_T("initQuantTables");

	int i, j, row, col;
	double t, u;
	
	for ( i = 0; i < 64; ++i)
	{
		t = (int)((YQT[i]*sf+50)*0.01);
		if (t < 1) {
			t = 1;
		} else if (t > 255) {
			t = 255;
		}
		YTable[ZigZag[i]] = t;
	}

	for ( j = 0; j < 64; j++)
	{
		u = (int)((UVQT[j]*sf+50)*0.01);
		if (u < 1) {
			u = 1;
		} else if (u > 255) {
			u = 255;
		}
		UVTable[ZigZag[j]] = u;
	}
	int k = 0;
	for ( row = 0; row < 8; ++row)
	{
		for ( col = 0; col < 8; ++col)
		{
			fdtbl_Y[k]  = (1 / (YTable [ ZigZag[k] ] * aasf[ row ] * aasf[ col ] * 8));
			fdtbl_UV[k] = (1 / (UVTable[ ZigZag[k] ] * aasf[ row ] * aasf[ col ] * 8));
			k += 1;
		}
	}
}

void init_encoder( unsigned char quality )
{
	_T("init_encoder");

	short sf = 0;
	if (quality < 50) {
		sf = 5000 / quality;
	} else {
		sf = 200 - ( quality<<1 );
	}
	
	initHuffmanTbl();
	
	initCategoryNumber();
	
	initQuantTables(sf);
	
}

inline void writeAPP0( OUTPUT output )
{
	_T("writeAPP0");

	IOVAR;
	writeWord(0xFFE0);	// marker
	writeWord(16);		// length
	writeByte(0x4A);	// J
	writeByte(0x46);	// F
	writeByte(0x49);	// I
	writeByte(0x46);	// F
	writeByte(0);		// = "JFIF",'\0'
	writeByte(1);		// versionhi
	writeByte(1);		// versionlo
	writeByte(0);		// xyunits
	writeWord(1);		// xdensity
	writeWord(1);		// ydensity
	writeByte(0);		// thumbnwidth
	writeByte(0);		// thumbnheight	
}

inline void writeDQT( OUTPUT output )
{
	_T("writeDQT");

	IOVAR;
	writeWord(0xFFDB);	// marker
	writeWord(132);     // length
	writeByte(0);
	int i;
	
	for (i = 0; i < 64; i++)
	{
		writeByte( YTable[i] );
	}
	
	writeByte(1);
	
	for (i = 0; i < 64; i++)
	{
		writeByte( UVTable[i] );
	}	
}

inline void writeSOF0( OUTPUT output, int width, int height )
{
	_T("writeSOF0");

	IOVAR;
	writeWord(0xFFC0);	// marker
	writeWord(17);		// length, truecolor YUV JPG
	writeByte(8);		// precision
	writeWord( height );
	writeWord( width );
	writeByte(3);		// nrofcomponents
	writeByte(1);		// IdY
	writeByte(0x11);	// HVY
	writeByte(0);		// QTY
	writeByte(2);		// IdU
	writeByte(0x11);	// HVU
	writeByte(1);		// QTU
	writeByte(3);		// IdV
	writeByte(0x11);	// HVV
	writeByte(1);		// QTV	
}

void writeDHT( OUTPUT output )
{
	_T("writeDHT");

	IOVAR;
	int i;
	
	writeWord(0xFFC4); // marker
	writeWord(0x01A2); // length
	
	writeByte(0); // HTYDCinfo
	for (i = 0; i < 16; i++)
	{
		writeByte(std_dc_luminance_nrcodes[i + 1]);
	}
	for (i = 0; i <= 11; i++)
	{
		writeByte(std_dc_luminance_values[i]);
	}
	
	writeByte(0x10); // HTYACinfo
	for (i = 0; i < 16; i++)
	{
		writeByte(std_ac_luminance_nrcodes[i + 1]);
	}
	for (i = 0; i <= 161; i++)
	{
		writeByte(std_ac_luminance_values[i]);
	}
	
	writeByte(1); // HTUDCinfo
	for (i = 0; i < 16; i++)
	{
		writeByte(std_dc_chrominance_nrcodes[i + 1]);
	}
	for (i = 0; i <= 11; i++)
	{
		writeByte(std_dc_chrominance_values[i]);
	}
	
	writeByte(0x11); // HTUACinfo
	for (i = 0; i < 16; i++)
	{
		writeByte(std_ac_chrominance_nrcodes[i + 1]);
	}
	for (i = 0; i <= 161; i++)
	{
		writeByte(std_ac_chrominance_values[i]);
	}
}

void writeSOS( OUTPUT output )
{
	_T("writeSOS");

	IOVAR;
	writeWord(0xFFDA);	// marker
	writeWord(12);		// length
	writeByte(3);		// nrofcomponents
	writeByte(1);		// IdY
	writeByte(0);		// HTY
	writeByte(2);		// IdU
	writeByte(0x11);	// HTU
	writeByte(3);		// IdV
	writeByte(0x11);	// HTV
	writeByte(0);		// Ss
	writeByte(0x3f);	// Se
	writeByte(0);		// Bf
}

void RGB2YUV( unsigned int *input,
			  int xpos, int ypos,
			  int width, int height )
{
	_T("RGB2YUV");

	int k = 0; // index into 64-element block arrays
	int j, y, i, x;
	unsigned int pixel;
	double r, g, b;
	
	for ( j = 0; j < 8; j++)
	{
		y = ypos + j;
		if (y >= height)
			y = height - 1;
		
		for (i = 0; i < 8; i++)
		{
			x = xpos + i;
			if (x >= width)
				x = width - 1;
					
//			pixel = input[ 4 * (y * width + x) ];
			pixel = input[ (y * width + x) ];
/*			if (sourceBitmapData)
			{
				pixel = sourceBitmapData.getPixel32(x, y);
			}
			else
			{
				sourceByteArray.position = 4 * (y * width + x);
				pixel = sourceByteArray.readUnsignedInt();
			}
			*/
			/*			r = (double)( (pixel >> 16) & 0xFF );
			 g = (double)( (pixel >> 8) & 0xFF );
			 b = (double)( pixel & 0xFF );
			 */
			b = (double)( (pixel >> 24) & 0xFF );
			g = (double)( (pixel >> 16) & 0xFF );
			r = (double)( (pixel >> 8) & 0xFF );
			
			YDU[ k ] =  0.29900 * r + 0.58700 * g + 0.11400 * b - 128.0;
			UDU[ k ] = -0.16874 * r - 0.33126 * g + 0.50000 * b;
			VDU[ k ] =  0.50000 * r - 0.41869 * g - 0.08131 * b;
			
			k+=1;
		}
	}
}


/**
 *  @private
 */
double* fDCTQuant( double* data, double* fdtbl )
{
	_T("fDCTQuant");

	int dataOff = 0;
	int i;
	double tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp10, tmp11, tmp12, tmp13;
	double z1, z2, z3, z4, z5, z11, z13;
	
	for (i = 0; i < 8; i++)
	{
		tmp0 = data[dataOff + 0] + data[dataOff + 7];
		tmp7 = data[dataOff + 0] - data[dataOff + 7];
		tmp1 = data[dataOff + 1] + data[dataOff + 6];
		tmp6 = data[dataOff + 1] - data[dataOff + 6];
		tmp2 = data[dataOff + 2] + data[dataOff + 5];
		tmp5 = data[dataOff + 2] - data[dataOff + 5];
		tmp3 = data[dataOff + 3] + data[dataOff + 4];
		tmp4 = data[dataOff + 3] - data[dataOff + 4];
		
		tmp10 = tmp0 + tmp3;	// phase 2
		tmp13 = tmp0 - tmp3;
		tmp11 = tmp1 + tmp2;
		tmp12 = tmp1 - tmp2;
		
		data[dataOff + 0] = tmp10 + tmp11; // phase 3
		data[dataOff + 4] = tmp10 - tmp11;
		
		z1 = (tmp12 + tmp13) * 0.707106781; // c4
		data[dataOff + 2] = tmp13 + z1; // phase 5
		data[dataOff + 6] = tmp13 - z1;
		
		// Odd part
		tmp10 = tmp4 + tmp5; // phase 2
		tmp11 = tmp5 + tmp6;
		tmp12 = tmp6 + tmp7;
		
		// The rotator is modified from fig 4-8 to avoid extra negations.
		z5 = (tmp10 - tmp12) * 0.382683433; // c6
		z2 = 0.541196100 * tmp10 + z5; // c2 - c6
		z4 = 1.306562965 * tmp12 + z5; // c2 + c6
		z3 = tmp11 * 0.707106781; // c4
		
		z11 = tmp7 + z3; // phase 5
		z13 = tmp7 - z3;
		
		data[dataOff + 5] = z13 + z2; // phase 6
		data[dataOff + 3] = z13 - z2;
		data[dataOff + 1] = z11 + z4;
		data[dataOff + 7] = z11 - z4;
		
		dataOff += 8; // advance pointer to next row
	}
	
	// Pass 2: process columns.
	dataOff = 0;
	for (i = 0; i < 8; i++)
	{
		tmp0 = data[dataOff +  0] + data[dataOff + 56];
		tmp7 = data[dataOff +  0] - data[dataOff + 56];
		tmp1 = data[dataOff +  8] + data[dataOff + 48];
		tmp6 = data[dataOff +  8] - data[dataOff + 48];
		tmp2 = data[dataOff + 16] + data[dataOff + 40];
		tmp5 = data[dataOff + 16] - data[dataOff + 40];
		tmp3 = data[dataOff + 24] + data[dataOff + 32];
		tmp4 = data[dataOff + 24] - data[dataOff + 32];
		
		// Even par
		tmp10 = tmp0 + tmp3; // phase 2
		tmp13 = tmp0 - tmp3;
		tmp11 = tmp1 + tmp2;
		tmp12 = tmp1 - tmp2;
		
		data[dataOff +  0] = tmp10 + tmp11; // phase 3
		data[dataOff + 32] = tmp10 - tmp11;
		
		z1 = (tmp12 + tmp13) * 0.707106781; // c4
		data[dataOff + 16] = tmp13 + z1; // phase 5
		data[dataOff + 48] = tmp13 - z1;
		
		// Odd part
		tmp10 = tmp4 + tmp5; // phase 2
		tmp11 = tmp5 + tmp6;
		tmp12 = tmp6 + tmp7;
		
		// The rotator is modified from fig 4-8 to avoid extra negations.
		z5 = (tmp10 - tmp12) * 0.382683433; // c6
		z2 = 0.541196100 * tmp10 + z5; // c2 - c6
		z4 = 1.306562965 * tmp12 + z5; // c2 + c6
		z3 = tmp11 * 0.707106781; // c4
		
		z11 = tmp7 + z3; // phase 5 */
		z13 = tmp7 - z3;
		
		data[dataOff + 40] = z13 + z2; // phase 6
		data[dataOff + 24] = z13 - z2;
		data[dataOff +  8] = z11 + z4;
		data[dataOff + 56] = z11 - z4;
		
		dataOff+=1; // advance pointer to next column
	}
	
	double v;
	double fv;
	// Quantize/descale the coefficients
	for (i = 0; i < 64; i++)
	{
		// Apply the quantization and scaling factor
		// and round to nearest integer
		v = data[i] * fdtbl[i];
		fv = floor( v );
		if ( fabs( v-fv ) < 0.5 )
			data[i] = fv;
		else
			data[i] = fv + 1;
//		data[i] = round(  );
	}
	
	return data;
}

//double processDU( CDU:Array, fdtbl:Array, DC:Number, HTDC:Array, HTAC:Array )
double processDU(  OUTPUT output, int* bytenew, int* bytepos, double* CDU, double* fdtbl, double DC, bitstring* HTDC, bitstring* HTAC )
{
	_T("processDU");

	bitstring EOB = HTAC[0x00];
	bitstring M16zeroes = HTAC[0xF0];
	int i;
	
	fDCTQuant( CDU, fdtbl);
	
	// ZigZag reorder
	for (i = 0; i < 64; i++)
	{
		DU[ZigZag[i]] = CDU[i];
	}
	
	int Diff = DU[0] - DC;
	DC = DU[0];
	
	// Encode DC
	if (Diff == 0)
	{
		writeBits( output, bytenew, bytepos, HTDC[0] ); // Diff might be 0
	}
	else
	{
		writeBits( output, bytenew, bytepos, HTDC[category[32767 + Diff]] );
		writeBits( output, bytenew, bytepos, bitcode[32767 + Diff]) ;
	}
	
	// Encode ACs
	int end0pos = 63;
	for (; (end0pos > 0) && (DU[end0pos] == 0); end0pos--)
	{
	}
	
	// end0pos = first element in reverse order != 0
	if (end0pos == 0)
	{
		writeBits( output, bytenew, bytepos, EOB);
		return DC;
	}
	
	i = 1;
	while (i <= end0pos)
	{
		int startpos = i;
		for (; (DU[i] == 0) && (i <= end0pos); i++)
		{
		}
		int nrzeroes = i - startpos;
		
		if (nrzeroes >= 16)
		{
			int nrmarker;
			for ( nrmarker = 1; nrmarker <= nrzeroes / 16; nrmarker++)
			{
				writeBits( output, bytenew, bytepos, M16zeroes);
			}
			nrzeroes = (int)( nrzeroes & 0xF);
		}
		
		writeBits( output, bytenew, bytepos, HTAC[ (int)(nrzeroes * 16 + category[ (int)(32767 + DU[i]) ]) ] );
		writeBits( output, bytenew, bytepos, bitcode[ (int)(32767 + DU[i]) ] );
		
		i+=1;
	}
	
	if (end0pos != 63)
		writeBits( output, bytenew, bytepos, EOB );
	
	return DC;
}

void internal_encode( OUTPUT output, unsigned int* input, int width, int height, int yeldFreq )
{
	_T("internal_encode");

	IOVAR;
	int bytenew = 0;
	int bytepos = 7;
	int yeld;
	
	double DCY = 0.0;
	double DCU = 0.0;
	double DCV = 0.0;

	writeWord( 0xFFD8 ); //SOI
	writeAPP0( output );
	writeDQT( output );
	writeSOF0( output, width, height );
	writeDHT( output );
	writeSOS( output );
	
	int ypos, xpos; 
	
	for ( ypos = 0; ypos < height; ypos += 8)
	{
		for ( xpos = 0; xpos < width; xpos += 8)
		{			
			RGB2YUV( (unsigned int*)input, xpos, ypos, width, height );
			
			DCY = processDU( output, &bytenew, &bytepos, YDU, fdtbl_Y, DCY, YDC_HT, YAC_HT);
			DCU = processDU( output, &bytenew, &bytepos, UDU, fdtbl_UV, DCU, UVDC_HT, UVAC_HT);
			DCV = processDU( output, &bytenew, &bytepos, VDU, fdtbl_UV, DCV, UVDC_HT, UVAC_HT);

			yeld += 1;
			if ( yeld > yeldFreq ) {
				yeld = 0;
				flyield();
			}

		}
	}
	
	// Do the bit alignment of the EOI marker
	if (bytepos >= 0)
	{
		bitstring fillbits;
		fillbits.len = bytepos + 1;
		fillbits.val = (1 << (bytepos + 1)) - 1;
		writeBits(output, &bytenew, &bytepos, fillbits);
	}
	
	// Add EOI
	writeWord(0xFFD9);
	
}


AS3_Val encodeSync( void *data, AS3_Val args )
{
	_T("encodeSync");
	
	int image_width = 0, image_height = 0, quality = 0;	
	AS3_Val source, dest;
	
	AS3_ArrayValue( args, "AS3ValType, AS3ValType, IntType, IntType, IntType", &source, &dest, &image_width, &image_height, &quality );
	
	
	if ( !initialized ) {
		init_encoder( quality );
		initialized = 1;
	}
	
	int input_size = sizeof(unsigned int)*image_width*image_height;
	unsigned int *input = (unsigned int*)malloc( input_size );	
	
	AS3_ByteArray_seek( source, 0, SEEK_SET );
	AS3_ByteArray_readBytes( input, source, input_size );

#ifdef FILE_BA 	
	FILE *output = funopen((void *)dest, readba, writeba, seekba, closeba);
	
	internal_encode( (OUTPUT)output, input, image_width, image_height, 0 );
	
	fclose( output );
#else
	
	internal_encode( (OUTPUT)dest, input, image_width, image_height, 0 );
	
	AS3_Val zero = AS3_Int(0);
	AS3_SetS( dest, "position", zero);
	AS3_Release(zero);
	
#endif
	
	free( input );	
	
	AS3_Release(dest);
	AS3_Release(source);
	AS3_Release(args);
	
	return AS3_Null();
}

AS3_Val encodeAsync( void *data, AS3_Val args )
{
	_T("encodeAsync");
	int image_width = 0, image_height = 0, quality = 0, yeldFreq;	
	AS3_Val source, dest;
	
	AS3_ArrayValue( args, "AS3ValType, AS3ValType, IntType, IntType, IntType, IntType", &source, &dest, &image_width, &image_height, &quality, &yeldFreq );
	
	if ( !initialized ) {
		init_encoder( quality );
		initialized = 1;
	}
	
	unsigned int *input = (unsigned int*)malloc( sizeof(unsigned int)*image_width*image_height );
	
	AS3_ByteArray_seek( source, 0, SEEK_SET );
	AS3_ByteArray_readBytes( input, source, image_width*image_height*4 );
	
#ifdef FILE_BA 	
	FILE *output = funopen((void *)dest, readba, writeba, seekba, closeba);
	
	internal_encode( (OUTPUT)output, input, image_width, image_height, yeldFreq );
	
	fclose( output );
#else
	
	internal_encode( (OUTPUT)dest, input, image_width, image_height, yeldFreq );
	
	AS3_Val zero = AS3_Int(0);
	AS3_SetS( dest, "position", zero);
	AS3_Release(zero);
	
#endif
	
	free( input );	
	
	AS3_Release(dest);
	AS3_Release(source);
	AS3_Release(args);
	
	return AS3_Null();
}

int main()
{
	_T("Enter main");
	initialized = 0;
	AS3_Val _encodeSingleSyncFunc = AS3_Function( NULL, encodeSync );
	AS3_Val _encodeSingleAsyncFunc = AS3_FunctionAsync( NULL, encodeAsync );
	
	AS3_Val libjpg = AS3_Object("encode: AS3ValType, encodeAsync: AS3ValType", 
								/*{0}*/_encodeSingleSyncFunc, 
								/*{1}*/_encodeSingleAsyncFunc
								);
	
	AS3_Release( _encodeSingleSyncFunc );
	AS3_Release( _encodeSingleAsyncFunc );	
	AS3_LibInit( libjpg );
	return 0;
}
