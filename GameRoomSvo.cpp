#include "GameRoomSvo.h"

GameRoomMemberSvo::GameRoomMemberSvo()
{
}

GameRoomMemberSvo::GameRoomMemberSvo(long id, std::string name)
{
    Id = id;
    Name = name;
}

GameRoomMemberSvo* GameRoomMemberSvo::Read(unsigned char* bytes, int len)
{
    GameRoomMemberSvo* svo = new GameRoomMemberSvo();
    ByteBuffer buffer(bytes, len);

    svo->Id = buffer.ReadInt64();
    svo->Name = (char*)buffer.ReadString();
    svo->Type = buffer.ReadInt32();
    return svo;
}

unsigned char* GameRoomMemberSvo::Write(GameRoomMemberSvo* svo)
{
    ByteBuffer buffer;
    buffer.WriteInt64(svo->Id)
        ->WriteString(svo->Name)
        ->WriteInt32(svo->Type);
    return buffer.Getbuffer();
}


GameRoomSvo::GameRoomSvo()
{
    RoomId = GetAddress();
    //Members = new std::vector<GameRoomMemberSvo*>();
}

long GameRoomSvo::GetAddress()
{
    return (long)this;
}

GameRoomSvo* GameRoomSvo::Read(unsigned char* bytes, int len)
{
    GameRoomSvo* svo = new GameRoomSvo();
    ByteBuffer buffer(bytes, len);
    svo->RoomId = buffer.ReadInt32();
    int size = buffer.ReadInt32();
    for (int i = 0; i < size; i++)
    {
        svo->Members.push_back(GameRoomMemberSvo::Read(buffer.ReadBytes(),buffer.GetBytesLen()));
    }
    return svo;
}

unsigned char* GameRoomSvo::Write(GameRoomSvo* value)
{
    ByteBuffer buffer;
    buffer.WriteInt32(value->RoomId)
        ->WriteInt32(value->Members.size());
    for (int i = 0; i < value->Members.size(); i++)
        buffer.WriteBytes(GameRoomMemberSvo::Write(value->Members[i]),buffer.GetBytesLen());
    return buffer.Getbuffer();
}
