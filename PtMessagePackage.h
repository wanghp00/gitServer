#pragma once
#include "ByteBuffer.h"
#include "BitConverter.h"

class PtMessagePackage
{
public:
	int MessageId;
	bool HasContent = false;
	unsigned char* m_Content;
	int content_len = 0;
	bool IsCompress = false;
	~PtMessagePackage();
	unsigned char* GetContent();
    void SetContent(unsigned char* value, int len);
	static PtMessagePackage* Build(int messageId);
	//static PtMessagePackage* Build(int messageId, unsigned char* content, int content_len, bool compress = true);
	static PtMessagePackage* Build(int messageId, unsigned char* content, int content_len);
	static PtMessagePackage* Build(int messageId, bool compress, int pars);
	static PtMessagePackage* Build(int messageId, bool compress, long pars, unsigned int upars);
	static PtMessagePackage* Read(unsigned char* bytes,int len);
	static void Write(PtMessagePackage* info, unsigned char* data, int* len);
	void Dispose();
};