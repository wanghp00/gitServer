#include "Message.h"

void Message::SetClient(ENetPeer* client)
{
    Client = client;
}

void Message::SetData(unsigned char* data, int len)
{
    unsigned char* d = (unsigned char*)malloc(len);
    memcpy(d, data, len);
    Data = d;
    DataLen = len;
}

Message::~Message()
{
    if (Data != NULL)
        free(Data);
}

ENetPeer* Message::GetClient()
{
    return Client;
}

unsigned char* Message::GetData()
{
    return Data;
}

int Message::GetDataLen()
{
    return DataLen;
}

Message::Message(ENetPeer* client, unsigned char* data, int len) {
    SetData(data,len);
    SetClient(client);
}