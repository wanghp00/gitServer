#include "GameServerData.h"

GameRoomSvo GameServerData::GameRoom;
std::vector<GamePlayerSvo*> GameServerData::GamePlayerList;
int GameServerData::EnterGameRoom(long roldId, std::string roleName) {
    for (int i = 0; i < GameRoom.Members.size(); i++)
    {
        if (GameRoom.Members[i]->Id == roldId) {
            return -1;
        }
    }
    GameRoomMemberSvo* tmp = new GameRoomMemberSvo(roldId, roleName);
    GameRoom.Members.push_back(tmp);
    return 0;
}

void GameServerData::SetGameMemeberReady(long roleId) {
    for (int i = 0; i < GameRoom.Members.size(); i++)
    {
        if (GameRoom.Members[i]->Id == roleId)
            GameRoom.Members[i]->Type = 1;
    }
}

bool GameServerData::IsAllReadyInGameRoom() {
    for (int i = 0; i < GameRoom.Members.size(); i++)
    {
        if (GameRoom.Members[i]->Type == 0) 
            return false;
    }
    return true;
}

GamePlayerSvo* GameServerData::AddNewPlayer() {
    GamePlayerSvo* player = new GamePlayerSvo();
    GamePlayerList.push_back(player);
    return player;
}