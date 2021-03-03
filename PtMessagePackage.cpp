#include "PtMessagePackage.h"

PtMessagePackage::~PtMessagePackage()
{
    if (m_Content != NULL)
    {
        delete[] m_Content;
        //free(m_Content);
        m_Content = NULL;
    }
}

//获取后注意释放
unsigned char* PtMessagePackage::GetContent()
{
    unsigned char* tmp = new unsigned char[content_len]();
    memcpy(tmp, m_Content, content_len);
	return tmp;
}

void PtMessagePackage::SetContent(unsigned char* value, int len)
{
	if (value != NULL)
	{
		m_Content = value;
        content_len = len;
		HasContent = true;
	}
}

PtMessagePackage* PtMessagePackage::Build(int messageId)
{
	PtMessagePackage* package = new PtMessagePackage();
	package->MessageId = messageId;
	return package;
}

//PtMessagePackage* PtMessagePackage::Build(int messageId, unsigned char* content, int content_len, bool compress = true)
PtMessagePackage* PtMessagePackage::Build(int messageId, unsigned char* content, int content_len)
{
    //compress = true;
	PtMessagePackage* package = PtMessagePackage::Build(messageId);
	package->IsCompress = true;//默认传参有问题？
	package->m_Content = content;
    package->content_len = content_len;
	return package;
}

PtMessagePackage* PtMessagePackage::Build(int messageId, bool compress, int pars)
{
    ByteBuffer* buffer = new ByteBuffer();
    buffer->WriteInt32(pars);
    unsigned char* tmp = buffer->Getbuffer();
    int len = buffer->GetBytesLen();
    delete buffer;
    buffer = NULL;
    return Build(messageId, tmp, len, compress);
}

PtMessagePackage* PtMessagePackage::Build(int messageId, bool compress, long pars, unsigned int upars)
{
    ByteBuffer* buffer = new ByteBuffer();
    buffer->WriteInt64(pars);
    buffer->WriteUInt32(upars);
    unsigned char* tmp = buffer->Getbuffer();
    int len = buffer->GetBytesLen();
    delete buffer;
    buffer = NULL;
    return Build(messageId, tmp, len, compress);
}

PtMessagePackage* PtMessagePackage::Read(unsigned char* bytes, int len)
{
    ByteBuffer* buffer = new ByteBuffer(bytes, len);
    PtMessagePackage* info = new PtMessagePackage();
    info->MessageId = buffer->ReadInt32();
    info->HasContent = buffer->ReadBool();
    if (info->HasContent)
    {
        info->IsCompress = buffer->ReadBool();
        //没有做字节压缩，所以不判断
        info->m_Content = buffer->ReadBytes();
    }
    delete buffer;
    buffer = NULL;
    return info;
}

/// <summary>
/// 
/// </summary>
/// <param name="info"></param>
/// <param name="data">返回数组</param>
/// <param name="len">返回数组长度</param>
void PtMessagePackage::Write(PtMessagePackage* info, unsigned char* data, int* len)
{
    ByteBuffer* buffer = new ByteBuffer();
    buffer->WriteInt32(info->MessageId);
    buffer->WriteBool(info->HasContent);
    if (info->HasContent)
    {
        buffer->WriteBool(info->IsCompress);
        //因为没移植压缩字节的代码，所以不去做判断了
        buffer->WriteBytes(info->m_Content, info->content_len);
    }
    data = buffer->Getbuffer();
    *len = buffer->GetBytesLen();
    if (info != NULL)
    {
        delete info;
        info = NULL;
    }
    if (buffer != NULL)
    {
        delete buffer;
        buffer = NULL;
    }
}

void PtMessagePackage::Dispose()
{
    
}
