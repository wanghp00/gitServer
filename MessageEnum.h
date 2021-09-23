#pragma once
enum class S2CMessageType
{
    ResponseClientConnected,
    ResponseEnterRoom,
    ResponseSyncKeyframes,
    ResponsePlayerReady,
    ResponseInitPlayer,
    ResponseAllPlayerReady,
    ResponsePlayerProperty
};

enum class C2SMessageType
{
    RequestEnterRoom,
    RequestSyncClientKeyframes,
    RequestInitPlayer,
    RequestPlayerReady,
    RequestPlayerProperty
};