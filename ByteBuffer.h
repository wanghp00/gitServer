#pragma once
#include <string>
#include "BitConverter.h"

class ByteBuffer {
private:
    unsigned char* bytes;
    int bytes_len;
    int position = 0;
    void Copy(unsigned char* value, int clen);
    unsigned char* Get(int length);
public:
    ByteBuffer(unsigned char* value, int clen);
    ByteBuffer();
    ~ByteBuffer();

    unsigned char* Getbuffer();
    void ResetPosition();

    int GetPosition();
    int GetBytesLen();
    unsigned char* GetSource();
    void SetSource(unsigned char* value, int clen);

    ByteBuffer* WriteInt16(short int value);
    short int ReadInt16();
    ByteBuffer* WriteInt32(int value);
    int ReadInt32();
    ByteBuffer* WriteUInt32(unsigned int value);
    unsigned int ReadUInt32();
    ByteBuffer* WriteUInt16(unsigned short int value);
    unsigned short int ReadUInt16();
    ByteBuffer* WriteString(std::string value);
    unsigned char* ReadString();
    ByteBuffer* WriteBytes(unsigned char* value, int clen);
    unsigned char* ReadBytes();
    ByteBuffer* WriteByte(unsigned char value);
    unsigned char ReadByte();
    ByteBuffer* WriteBool(bool value);
    bool ReadBool();
    ByteBuffer* WriteInt64(long value);
    long ReadInt64();
    ByteBuffer* WriteUInt64(unsigned long value);
    unsigned long ReadUInt64();
    /*ByteBuffer* WriteFloat(float value);
    float ReadFloat();*/
    void Dispose();
};