#pragma once
#include "GameRoomSvo.h"
#include "GamePlayerSvo.h"
#include <vector>

class GameServerData {

public:
    static GameRoomSvo GameRoom;
    static int EnterGameRoom(long roldId, std::string roleName);
    static void SetGameMemeberReady(long roleId);
    static bool IsAllReadyInGameRoom();
    static GamePlayerSvo* AddNewPlayer();

private:
    static std::vector<GamePlayerSvo*> GamePlayerList;
};