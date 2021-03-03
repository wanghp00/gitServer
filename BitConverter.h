#pragma once
#include <iostream>
#include <string.h>
#include <memory>

class BitConverter {
public:
	static unsigned char* GetBytes(int value);
	static unsigned char* GetBytes(unsigned int value);
	static unsigned char* GetBytes(short int value);
	static unsigned char* GetBytes(unsigned short int value);
	static unsigned char* GetBytes(long value);
	static unsigned char* GetBytes(unsigned long value);
	static int ToInt32(unsigned char* value);
	static unsigned int ToUInt32(unsigned char* value);
	static short int ToInt16(unsigned char* value);
	static unsigned short int ToUInt16(unsigned char* value);
	static long ToInt64(unsigned char* value);
	static unsigned long ToUInt64(unsigned char* value);
};