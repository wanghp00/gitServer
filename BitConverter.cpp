#include "BitConverter.h"

unsigned char* BitConverter::GetBytes(int value)
{
	unsigned char* tmp = new unsigned char[4]();
	*tmp = value & 0xff;
	* (tmp + 1) = (value >> 8) & 0xff;
	* (tmp + 2) = (value >> 16) & 0xff;
	* (tmp + 3) = (value >> 24) & 0xff;
	return tmp;
}

unsigned char* BitConverter::GetBytes(unsigned int value)
{
	unsigned char* tmp = new unsigned char[4]();
	*tmp = value & 0xff;
	*(tmp + 1) = (value >> 8) & 0xff;
	*(tmp + 2) = (value >> 16) & 0xff;
	*(tmp + 3) = (value >> 24) & 0xff;
	return tmp;
}

unsigned char* BitConverter::GetBytes(short int value)
{
	unsigned char* tmp = new unsigned char[2]();
	*tmp = value & 0xff;
	*(tmp + 1) = (value >> 8) & 0xff;
	return tmp;
}

unsigned char* BitConverter::GetBytes(unsigned short int value)
{
	unsigned char* tmp = new unsigned char[2]();
	*tmp = value & 0xff;
	*(tmp + 1) = (value >> 8) & 0xff;
	return tmp;
}

unsigned char* BitConverter::GetBytes(long value)
{
	unsigned char* tmp = new unsigned char[8]();
	*tmp = value & 0xff;
	*(tmp + 1) = (value >> 8) & 0xff;
	*(tmp + 2) = (value >> 16) & 0xff;
	*(tmp + 3) = (value >> 24) & 0xff;
	*(tmp + 4) = (value >> 32) & 0xff;
	*(tmp + 5) = (value >> 40) & 0xff;
	*(tmp + 6) = (value >> 48) & 0xff;
	*(tmp + 7) = (value >> 56) & 0xff;
	return tmp;
}

unsigned char* BitConverter::GetBytes(unsigned long value)
{
	unsigned char* tmp = new unsigned char[8]();
	*tmp = value & 0xff;
	*(tmp + 1) = (value >> 8) & 0xff;
	*(tmp + 2) = (value >> 16) & 0xff;
	*(tmp + 3) = (value >> 24) & 0xff;
	*(tmp + 4) = (value >> 32) & 0xff;
	*(tmp + 5) = (value >> 40) & 0xff;
	*(tmp + 6) = (value >> 48) & 0xff;
	*(tmp + 7) = (value >> 56) & 0xff;
	return tmp;
}

int BitConverter::ToInt32(unsigned char* value)
{
	int ret = 0;
	unsigned int t1 = 0;
	unsigned int t2 = 0;
	unsigned int t3 = 0;
	unsigned int t4 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t3 |= *(value + 2);
	t4 |= *(value + 3);
	t2 <<= 8;
	t3 <<= 16;
	t4 <<= 24;
	ret = t1 | t2 | t3 | t4;
	return ret;
}

unsigned int BitConverter::ToUInt32(unsigned char* value)
{
	unsigned int ret = 0;
	unsigned int t1 = 0;
	unsigned int t2 = 0;
	unsigned int t3 = 0;
	unsigned int t4 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t3 |= *(value + 2);
	t4 |= *(value + 3);
	t2 <<= 8;
	t3 <<= 16;
	t4 <<= 24;
	ret = t1 | t2 | t3 | t4;
	return ret;
}

short int BitConverter::ToInt16(unsigned char* value)
{
	short int ret = 0;
	unsigned short int t1 = 0;
	unsigned short int t2 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t2 <<= 8;
	ret = t1 | t2;
	return ret;
}

unsigned short int BitConverter::ToUInt16(unsigned char* value)
{
	unsigned short int ret = 0;
	unsigned short int t1 = 0;
	unsigned short int t2 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t2 <<= 8;
	ret = t1 | t2;
	return ret;
}

long BitConverter::ToInt64(unsigned char* value)
{
	long ret = 0;
	unsigned long t1 = 0;
	unsigned long t2 = 0;
	unsigned long t3 = 0;
	unsigned long t4 = 0;
	unsigned long t5 = 0;
	unsigned long t6 = 0;
	unsigned long t7 = 0;
	unsigned long t8 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t3 |= *(value + 2);
	t4 |= *(value + 3);
	t5 |= *(value + 4);
	t6 |= *(value + 5);
	t7 |= *(value + 6);
	t8 |= *(value + 7);
	t2 <<= 8;
	t3 <<= 16;
	t4 <<= 24;
	t5 <<= 32;
	t6 <<= 40;
	t7 <<= 48;
	t8 <<= 56;
	ret = t1 | t2 | t3 | t4 | t5 |t6 | t7 | t8;
	return ret;
}

unsigned long BitConverter::ToUInt64(unsigned char* value)
{
	unsigned long ret = 0;
	unsigned long t1 = 0;
	unsigned long t2 = 0;
	unsigned long t3 = 0;
	unsigned long t4 = 0;
	unsigned long t5 = 0;
	unsigned long t6 = 0;
	unsigned long t7 = 0;
	unsigned long t8 = 0;
	t1 |= *(value);
	t2 |= *(value + 1);
	t3 |= *(value + 2);
	t4 |= *(value + 3);
	t5 |= *(value + 4);
	t6 |= *(value + 5);
	t7 |= *(value + 6);
	t8 |= *(value + 7);
	t2 <<= 8;
	t3 <<= 16;
	t4 <<= 24;
	t5 <<= 32;
	t6 <<= 40;
	t7 <<= 48;
	t8 <<= 56;
	ret = t1 | t2 | t3 | t4 | t5 | t6 | t7 | t8;
	return ret;
}
