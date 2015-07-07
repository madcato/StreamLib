// MD5.cpp: implementation of the MD5 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MD5.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// namespace stream
namespace stream
{
/// namespace util
namespace util
{

MD5::MD5()
{

}

MD5::~MD5()
{

}


std::string MD5::calculateToHex(char* buffer,int length)
{

	uMD5 md5 = calculateToMD5(buffer,length);

	std::string result = "";
	char paso[20];
	for(int i = 0 ; i < 16 ; i++)
	{
		sprintf(paso,"%02X",md5.buffer[i]);
		result += paso;
	}

	return  paso;
}


/* add, handling overflows correctly */
long shift(long x , long y)
{
	long paso = x >> y;

	long unos = 1;
	for(int i = 31 ; i > y ; i--)
	{
		unos |= unos << 1;
	}
	
	return paso & unos; 

}
long add(long x, long y)
{
  return ((x&0x7FFFFFFF) + (y&0x7FFFFFFF)) ^ (x&0x80000000) ^ (y&0x80000000);
}

/* MD5 rounds functions */
long R1(long A, long B, long C, long D, long X, long S, long T)
{
  long q = add(add(A, (B & C) | ((~B) & D)), add(X, T));
  return add((q << S) | (shift(q,(32 - S))), B);
}

long R2(long A, long B, long C, long D, long X, long S, long T)
{
  long q = add(add(A, (B & D) | (C & (~D))), add(X, T));
  return add((q << S) | (shift(q,(32 - S))), B);
}

long R3(long A, long B, long C, long D, long X, long S, long T)
{
  long q = add(add(A, B ^ C ^ D), add(X, T));
  return add((q << S) | (shift(q,(32 - S))), B);
}

long R4(long A, long B, long C, long D, long X, long S, long T)
{
  long q = add(add(A, C ^ (B | (~D))), add(X, T));
  return add((q << S) | (shift(q,(32 - S))), B);
}

/* main entry point */
MD5::uMD5 MD5::calculateToMD5(char* sInp,int length) {

  /* Calculate length in machine words, including padding */
  long wLen = (((length + 8) >> 6) + 1) << 4;
  long* X = new long[wLen];

  /* Convert string to array of words */
  long j = 4;
  

  int i = 0;
  
  for (i = 0; (i * 4) < length; i++)
  {
    X[i] = 0;
    for (j = 0; (j < 4) && ((j + i * 4) < length); j++)
    {
      X[i] += (sInp[(i * 4) + j]) << (j * 8);
    }
  }
  
  /* Append padding bits and length */
  if (j == 4)
  {
    X[i++] = 0x80;
  }
  else
  {
    X[i - 1] += 0x80 << (j * 8);
  }
  for(; i < wLen; i++) { X[i] = 0; }
  X[wLen - 2] = length * 8;

  /* hard coded initial values */
  long a = 0x67452301;
  long b = 0xefcdab89;
  long c = 0x98badcfe;
  long d = 0x10325476;

  /* Process each 16 word block in turn */
  for (i = 0; i < wLen; i += 16) {
    long aO = a;
    long bO = b;
    long cO = c;
    long dO = d;

    a = R1(a, b, c, d, X[i+ 0], 7 , 0xd76aa478);
    d = R1(d, a, b, c, X[i+ 1], 12, 0xe8c7b756);
    c = R1(c, d, a, b, X[i+ 2], 17, 0x242070db);
    b = R1(b, c, d, a, X[i+ 3], 22, 0xc1bdceee);
    a = R1(a, b, c, d, X[i+ 4], 7 , 0xf57c0faf);
    d = R1(d, a, b, c, X[i+ 5], 12, 0x4787c62a);
    c = R1(c, d, a, b, X[i+ 6], 17, 0xa8304613);
    b = R1(b, c, d, a, X[i+ 7], 22, 0xfd469501);
    a = R1(a, b, c, d, X[i+ 8], 7 , 0x698098d8);
    d = R1(d, a, b, c, X[i+ 9], 12, 0x8b44f7af);
    c = R1(c, d, a, b, X[i+10], 17, 0xffff5bb1);
    b = R1(b, c, d, a, X[i+11], 22, 0x895cd7be);
    a = R1(a, b, c, d, X[i+12], 7 , 0x6b901122);
    d = R1(d, a, b, c, X[i+13], 12, 0xfd987193);
    c = R1(c, d, a, b, X[i+14], 17, 0xa679438e);
    b = R1(b, c, d, a, X[i+15], 22, 0x49b40821);

    a = R2(a, b, c, d, X[i+ 1], 5 , 0xf61e2562);
    d = R2(d, a, b, c, X[i+ 6], 9 , 0xc040b340);
    c = R2(c, d, a, b, X[i+11], 14, 0x265e5a51);
    b = R2(b, c, d, a, X[i+ 0], 20, 0xe9b6c7aa);
    a = R2(a, b, c, d, X[i+ 5], 5 , 0xd62f105d);
    d = R2(d, a, b, c, X[i+10], 9 ,  0x2441453);
    c = R2(c, d, a, b, X[i+15], 14, 0xd8a1e681);
    b = R2(b, c, d, a, X[i+ 4], 20, 0xe7d3fbc8);
    a = R2(a, b, c, d, X[i+ 9], 5 , 0x21e1cde6);
    d = R2(d, a, b, c, X[i+14], 9 , 0xc33707d6);
    c = R2(c, d, a, b, X[i+ 3], 14, 0xf4d50d87);
    b = R2(b, c, d, a, X[i+ 8], 20, 0x455a14ed);
    a = R2(a, b, c, d, X[i+13], 5 , 0xa9e3e905);
    d = R2(d, a, b, c, X[i+ 2], 9 , 0xfcefa3f8);
    c = R2(c, d, a, b, X[i+ 7], 14, 0x676f02d9);
    b = R2(b, c, d, a, X[i+12], 20, 0x8d2a4c8a);

    a = R3(a, b, c, d, X[i+ 5], 4 , 0xfffa3942);
    d = R3(d, a, b, c, X[i+ 8], 11, 0x8771f681);
    c = R3(c, d, a, b, X[i+11], 16, 0x6d9d6122);
    b = R3(b, c, d, a, X[i+14], 23, 0xfde5380c);
    a = R3(a, b, c, d, X[i+ 1], 4 , 0xa4beea44);
    d = R3(d, a, b, c, X[i+ 4], 11, 0x4bdecfa9);
    c = R3(c, d, a, b, X[i+ 7], 16, 0xf6bb4b60);
    b = R3(b, c, d, a, X[i+10], 23, 0xbebfbc70);
    a = R3(a, b, c, d, X[i+13], 4 , 0x289b7ec6);
    d = R3(d, a, b, c, X[i+ 0], 11, 0xeaa127fa);
    c = R3(c, d, a, b, X[i+ 3], 16, 0xd4ef3085);
    b = R3(b, c, d, a, X[i+ 6], 23,  0x4881d05);
    a = R3(a, b, c, d, X[i+ 9], 4 , 0xd9d4d039);
    d = R3(d, a, b, c, X[i+12], 11, 0xe6db99e5);
    c = R3(c, d, a, b, X[i+15], 16, 0x1fa27cf8);
    b = R3(b, c, d, a, X[i+ 2], 23, 0xc4ac5665);

    a = R4(a, b, c, d, X[i+ 0], 6 , 0xf4292244);
    d = R4(d, a, b, c, X[i+ 7], 10, 0x432aff97);
    c = R4(c, d, a, b, X[i+14], 15, 0xab9423a7);
    b = R4(b, c, d, a, X[i+ 5], 21, 0xfc93a039);
    a = R4(a, b, c, d, X[i+12], 6 , 0x655b59c3);
    d = R4(d, a, b, c, X[i+ 3], 10, 0x8f0ccc92);
    c = R4(c, d, a, b, X[i+10], 15, 0xffeff47d);
    b = R4(b, c, d, a, X[i+ 1], 21, 0x85845dd1);
    a = R4(a, b, c, d, X[i+ 8], 6 , 0x6fa87e4f);
    d = R4(d, a, b, c, X[i+15], 10, 0xfe2ce6e0);
    c = R4(c, d, a, b, X[i+ 6], 15, 0xa3014314);
    b = R4(b, c, d, a, X[i+13], 21, 0x4e0811a1);
    a = R4(a, b, c, d, X[i+ 4], 6 , 0xf7537e82);
    d = R4(d, a, b, c, X[i+11], 10, 0xbd3af235);
    c = R4(c, d, a, b, X[i+ 2], 15, 0x2ad7d2bb);
    b = R4(b, c, d, a, X[i+ 9], 21, 0xeb86d391);

    a = add(a, aO);
    b = add(b, bO);
    c = add(c, cO);
    d = add(d, dO);
  }

	md5Hash h;
	h.a = a;
	h.b = b;
	h.c = c;
	h.d = d;
	uMD5 h2;

	h2.md5 = h;
  return h2;//hex(a) + hex(b) + hex(c) + hex(d);
}

} // namespace util

} //namespace stream