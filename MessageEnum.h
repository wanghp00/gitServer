#pragma once
enum class S2CMessageType
{
    ResponseClientConnected,
    ResponseEnterRoom,
    ResponseSyncKeyframes,
    ResponsePlayerReady,
    ResponseInitPlayer,
    ResponseAllPlayerReady,
};

enum class C2SMessageType
{
    RequestEnterRoom,
    RequestSyncClientKeyframes,
    RequestInitPlayer,
    RequestPlayerReady,
};