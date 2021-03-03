#pragma once
#include <enet/enet.h>
#include <string.h>
class Message {
private:
    ENetPeer* Client;
    unsigned char* Data = NULL;
    int DataLen = 0;
    void SetClient(ENetPeer* client);
    void SetData(unsigned char* data, int len);

public:
    ~Message();
    ENetPeer* GetClient();
    unsigned char* GetData();
    int GetDataLen();
    Message(ENetPeer* client, unsigned char* data, int len);//������µ��ڴ棬���Ҳ����ͷ�ԭdata
};
