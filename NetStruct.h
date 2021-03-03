#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "BitFloat.h"
#include <stdio.h>
struct PlayerProperty;
struct SingleOperatorData {
public:
    long int id;
    unsigned int sequence;
    unsigned char controlFlag;
};

struct StaticStructHelper {
public:
    long id;
    unsigned int sequence;
    unsigned char controlFlag;

    template <typename T>
    static int StructToBytes(T* structObj, unsigned char* ret, int* len);
    static int PropertyToBytes(PlayerProperty* structObj, unsigned char* ret, int* len);

    template <typename T>
    static T* BytesToStruct(unsigned char* bytes, int len, T t);
    static SingleOperatorData* BytesToSingle(unsigned char* bytes, int len);
};

struct MutiData {
public:
    unsigned int sequence;
    /// <summary>
    /// 0:w,1:a,2:s,3:d,4:null
    /// </summary>
    std::vector<SingleOperatorData*> totalClients;
    static int StructToBytes(MutiData* structObj, unsigned char* ret, int* len);
    static MutiData* BytesToStruct(unsigned char* bytes, int len);
};

struct PlayerProperty {
    // λ��
public:
    BitVector3 position;
    // ��ת����������
    BitFloat x;
    BitFloat y;
    BitFloat z;
    //float x;
    // id����ǰ֡�š����������ͼ��
    long int id;
    unsigned int sequence;
    unsigned int readLoopIntervalMs;
};



