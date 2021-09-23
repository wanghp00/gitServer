#include "NetStruct.h"

int MutiData::StructToBytes(MutiData* structObj, unsigned char* ret, int* len)
{
    int offset = 0;
    int uintSize = sizeof(structObj->sequence);

    int singleOperatorDataSize = structObj->totalClients.size() * sizeof(SingleOperatorData);
    int loseConnectIdsDataSize = structObj->loseConnectIdsSize * sizeof(unsigned long int);
    int newConnectIdsDataSize = structObj->newConnectIdsSize * sizeof(unsigned long int);
    int totalClientsSizeSize = sizeof(unsigned int);
    int loseConnectIdsSizeSize = sizeof(unsigned int);
    int newConnectIdsSizeSizeSize = sizeof(unsigned int);
    int size = uintSize + singleOperatorDataSize + loseConnectIdsDataSize + newConnectIdsDataSize + totalClientsSizeSize + loseConnectIdsSizeSize + newConnectIdsSizeSizeSize;

    /*int SingleOperatorDataSize = structObj->totalClients.size() * sizeof(SingleOperatorData);
    int size = uintSize + SingleOperatorDataSize;*/
    //创建byte数组
    //unsigned char* bytes = new unsigned char[size]();
    unsigned char* bytes = (unsigned char*)malloc(size);

    //分配sequence的内存空间
    memcpy(bytes + offset, (unsigned char*)(&structObj->sequence), uintSize);
    offset += uintSize;
    // 分配totalClientsSize的内存空间
    memcpy(bytes + offset, (unsigned char*)(&structObj->totalClientsSize), totalClientsSizeSize);
    offset += totalClientsSizeSize;
    // 分配loseConnectIdsSizeSize的内存空间
    memcpy(bytes + offset, (unsigned char*)(&structObj->loseConnectIdsSize), loseConnectIdsSizeSize);
    offset += loseConnectIdsSizeSize;
    // 分配newConnectIdsSize的内存空间
    memcpy(bytes + offset, (unsigned char*)(&structObj->newConnectIdsSize), newConnectIdsSizeSizeSize);
    offset += newConnectIdsSizeSizeSize;
    ////分配uint的内存空间
    //memcpy(bytes + offset, (unsigned char*)(&structObj->sequence), uintSize);
    //offset += uintSize;
    //分配totalClients的内存空间
    for (SingleOperatorData* singleOperatorData : structObj->totalClients)
    {
        int singleSize = sizeof(SingleOperatorData);
        memcpy(bytes + offset, (unsigned char*)singleOperatorData, singleSize);
        offset += singleSize;
    }
    ret = bytes;
    *len = size;
    return 1;
}

MutiData* MutiData::BytesToStruct(unsigned char* bytes, int len)
{
    MutiData* result = new MutiData();
    int offset = 0;
    int uintSize = sizeof(unsigned int);
    int singleOperatorDataSize = sizeof(SingleOperatorData);
    // 首先是sequence的分配
    unsigned int* uintPtr = (unsigned int*)malloc(uintSize);
    memcpy((unsigned char*)uintPtr, bytes + offset, uintSize);
    int sequence = *uintPtr;
    free(uintPtr);
    result->sequence = sequence;
    offset += uintSize;

    // 其次是totalClients的分配
    int clients = (len - uintSize) / singleOperatorDataSize;
    //std::vector<SingleOperatorData*> totalClients = new std::vector<SingleOperatorData*>;
    //List<SingleOperatorData> totalClients = new List<SingleOperatorData>(clients);
    for (int i = 0; i < clients; i++) {
        SingleOperatorData* tmp = new SingleOperatorData();
        memcpy((unsigned char*)tmp, bytes + offset, singleOperatorDataSize);
        result->totalClients.push_back(tmp);
        offset += singleOperatorDataSize;
    }
    //result->totalClients = totalClients;
    return result;
}

template <typename T>
int StaticStructHelper::StructToBytes(T* structObj, unsigned char* ret, int* len) {
    //得到结构体的大小
    int size = sizeof(T);
    //创建byte数组
    unsigned char* bytes = new unsigned char[size];
    memcpy(bytes, (unsigned char*)structObj, size);
    ret = bytes;
    *len = size;
    return 0;
}

int StaticStructHelper::PropertyToBytes(PlayerProperty* structObj, unsigned char* ret, int* len) {
    //得到结构体的大小
    int size = sizeof(PlayerProperty);
    //创建byte数组
    unsigned char* bytes = new unsigned char[size];
    memcpy(bytes, (unsigned char*)structObj, size);
    ret = bytes;
    *len = size;
    return 0;
}

template <typename T>
T* StaticStructHelper::BytesToStruct(unsigned char* bytes, int len, T t) {
    // 得到结构体的大小       
    int size = sizeof(T);
    // byte数组长度小于结构体的大小
    if (size > len) {
        return NULL;
    }
    T* tmp = new T();
    memcpy((unsigned char*)tmp, bytes, size);
    return tmp;
}

SingleOperatorData* StaticStructHelper::BytesToSingle(unsigned char* bytes, int len) {
    // 得到结构体的大小       
    int size = sizeof(SingleOperatorData);
    // byte数组长度小于结构体的大小
    if (size > len) {
        return NULL;
    }
    SingleOperatorData* tmp = new SingleOperatorData();
    memcpy((unsigned char*)tmp, bytes, size);
    return tmp;
}
