#include "ByteBuffer.h"

ByteBuffer::ByteBuffer(unsigned char* value, int clen)
{
	SetSource(value, clen);
}

ByteBuffer::ByteBuffer()
{
	bytes = NULL;
	bytes_len = 0;
	position = 0;
}

ByteBuffer::~ByteBuffer()
{
	if (bytes != NULL)
	{
		delete[] bytes;
		bytes = NULL;
	}
}

void ByteBuffer::Copy(unsigned char* value, int clen)
{
	unsigned char* temps = new unsigned char[bytes_len + clen];
	memcpy(temps, bytes, bytes_len);
	memcpy(temps + position, value, clen);
	//memcpy(temps, bytes_len+clen, bytes, bytes_len);
	//memcpy(temps + position, bytes_len + clen, value, clen);
	//Buffer.BlockCopy(bytes, 0, temps, 0, bytes.Length);
	//Buffer.BlockCopy(value, 0, temps, position, value.Length);
	position += clen;
	/*if (value != NULL)
	{
		delete[] value;
		value = NULL;
	}*/
	if (bytes != NULL)
	{
		delete[] bytes;
		bytes = NULL;
	}
	bytes = temps;
	bytes_len += clen;
}

unsigned char* ByteBuffer::Get(int length)
{
	unsigned char* data = new unsigned char[length];
	memcpy(data, bytes + position, length);
	//Buffer.BlockCopy(bytes, position, data, 0, length);
	position += length;
	return data;
}

unsigned char* ByteBuffer::Getbuffer()
{
	return GetSource();
}

void ByteBuffer::ResetPosition()
{
	position = 0;
}

int ByteBuffer::GetPosition()
{
	return position;
}

int ByteBuffer::GetBytesLen()
{
	return bytes_len;
}

unsigned char* ByteBuffer::GetSource()
{
	unsigned char* tmp = new unsigned char[bytes_len]();
	memcpy(tmp, bytes, bytes_len);
	return tmp;
}

void ByteBuffer::SetSource(unsigned char* value, int clen)
{
	if (bytes != NULL)
	{
		delete[] bytes;
		bytes = NULL;
	}
	bytes = value;
	bytes_len = clen;
	ResetPosition();
}

ByteBuffer* ByteBuffer::WriteInt16(short value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp,2);
	return this;
}

short int ByteBuffer::ReadInt16()
{
	return BitConverter::ToInt16(Get(2));
}

ByteBuffer* ByteBuffer::WriteInt32(int value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp,4);
	return this;
}

int ByteBuffer::ReadInt32()
{
	return BitConverter::ToInt32(Get(4));
}

ByteBuffer* ByteBuffer::WriteUInt32(unsigned int value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp,4);
	return this;
}

unsigned int ByteBuffer::ReadUInt32()
{
	return BitConverter::ToUInt32(Get(4));
}

ByteBuffer* ByteBuffer::WriteUInt16(unsigned short value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp,2);
	return this;
}

unsigned short ByteBuffer::ReadUInt16()
{
	return BitConverter::ToUInt16(Get(2));
}

ByteBuffer* ByteBuffer::WriteString(std::string value)
{
	unsigned char* data = (unsigned char*)value.c_str();
	WriteInt32(value.length());
	Copy(data, value.length());
	return this;
}

unsigned char* ByteBuffer::ReadString()
{
	return Get(ReadInt32());
}

/// <summary>
/// 一定要由PtMessagePackage的content作为value传入，因为本函数中不释放该value，由PtMessagePackage的析构函数自行释放
/// </summary>
/// <param name="value"></param>
/// <param name="clen"></param>
/// <returns></returns>
ByteBuffer* ByteBuffer::WriteBytes(unsigned char* value, int clen)
{
	WriteInt32(clen);
	Copy(value,clen);
	return this;
}

unsigned char* ByteBuffer::ReadBytes()
{
	return Get(ReadInt32());
}

ByteBuffer* ByteBuffer::WriteByte(unsigned char value)
{
	unsigned char* tmp;
	*tmp = value;
	Copy(tmp,1);
	return this;
}

unsigned char ByteBuffer::ReadByte()
{
	return Get(1)[0];
}

ByteBuffer* ByteBuffer::WriteBool(bool value)
{
	unsigned char tmp = (unsigned char)value;
	WriteByte(tmp);
	return this;
}

bool ByteBuffer::ReadBool()
{
	return (bool)ReadByte();
}

ByteBuffer* ByteBuffer::WriteInt64(long value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp, 8);
	return this;
}

long ByteBuffer::ReadInt64()
{
	return BitConverter::ToInt64(Get(8));
}

ByteBuffer* ByteBuffer::WriteUInt64(unsigned long value)
{
	unsigned char* tmp = BitConverter::GetBytes(value);
	Copy(tmp, 8);
	return this;
}

unsigned long ByteBuffer::ReadUInt64()
{
	return BitConverter::ToUInt64(Get(8));
}

//ByteBuffer* ByteBuffer::WriteFloat(float value)
//{
//	Copy(BitConverter.GetBytes(value));
//	return this;
//}
//
//float ByteBuffer::ReadFloat()
//{
//	return BitConverter.ToSingle(Get(4), 0);
//}

void ByteBuffer::Dispose()
{
	position = 0;
	bytes = NULL;
}
