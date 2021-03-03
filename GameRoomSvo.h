#pragma once
#include "ByteBuffer.h"
#include <vector>
#include <string>

class GameRoomMemberSvo
{
public:
    long Id;
    std::string Name = "";
    int Type;
    GameRoomMemberSvo();
    GameRoomMemberSvo(long id, std::string name);
    static GameRoomMemberSvo* Read(unsigned char* bytes, int len);

    static unsigned char* Write(GameRoomMemberSvo* svo);
};

class GameRoomSvo
{
public:
    int RoomId;
    std::vector<GameRoomMemberSvo*> Members;
    //List<GameRoomMemberSvo> Members;

    GameRoomSvo();
    long GetAddress();
    static GameRoomSvo* Read(unsigned char* bytes, int len);
    static unsigned char* Write(GameRoomSvo* value);
};

