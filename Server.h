#pragma once
#include "NetStruct.h"
#include "PtMessagePackage.h"
#include "ServerListener.h"
#include "GamePlayerSvo.h"
#include "GameServerData.h"
//#include "BitFloat.h"
#include "Message.h"
#include <vector>
#include <iostream>
#include <algorithm>
class Server {
private:
    // 一个Server下面可以有多个ServerListener，目前只有一个
    //std::vector<ServerListener*> _listeners;
    ServerListener* _listeners = NULL;
    //std::vector<SingleOperatorData*> allClientsOperation;

    /// <summary>
    /// 将data广播给所有客户
    /// </summary>
    /// <param name="data"></param>
    void Broadcast(unsigned char* data, int len);
    void DataReceived(Message* msg);
    void ClientConnected(ENetPeer* peer);
    void ClientDisconnected(ENetPeer* peer);
public:
    // 当客户端连上的时候需要执行的事件
    //event EventHandler<Peer> ClientConnected;
    // 当客户端失去连接的时候需要执行的事件
    //event EventHandler<Peer> ClientDisconnected;
    // 当客户端发来消息的时候需要执行的事件
    //event EventHandler<Message> DataReceived;

    Server();

    ~Server();

    /// <summary>
    /// 服务器启动，自动设置绑定地址
    /// </summary>
    /// <param name="port">端口号</param>
    void Start(int port);

    /// <summary>
    /// 服务器启动，手动设定绑定地址以及端口号
    /// </summary>
    /// <param name="ipAddress">地址</param>
    /// <param name="port">端口号</param>
    void Start(ENetAddress* ipAddress, int port);

    // TODO 需要根据当前客户信息动态设置，目前是写死的
    /// <summary>
    /// 当客户刚连接上的时候需要发送客户一些信息，比如位置信息、旋转信息等等
    /// </summary>
    /// <returns></returns>
    void ComputeInitProperty(unsigned char* data, int* len);

    /// <summary>
    /// 获取所有的操作信息用以帮助客户端进行恢复
    /// </summary>
    /// <returns></returns>
    std::vector<MutiData*>* GetAllOperations();
        
    /// <summary>
    /// 将数据包进行广播
    /// </summary>
    /// <param name="package"></param>
    void Broadcast(PtMessagePackage* package);

    /// <summary>
    /// 将客户发来的消息进行缓存
    /// </summary>
    /// <param name="message"></param>
    void CacheClientInfo(PtMessagePackage* message);

    /// <summary>
    /// 获取当前服务器的帧号，因为目前只有一个listener，就直接取第一个
    /// </summary>
    /// <returns></returns>
    unsigned int GetCurrentSequence();

    /// <summary>
    /// 当收到客户端发来的消息后，触发DataReceived事件
    /// </summary>
    /// <param name="client">发送消息的客户</param>
    /// <param name="msg">发来的消息</param>
    void NotifyEndTransmissionRx(ENetPeer* client, unsigned char* msg, int len);

    /// <summary>
    /// 当客户连接后触发ClientConnected事件
    /// </summary>
    void NotifyClientConnected(ENetPeer* newClient);

    /// <summary>
    /// 当客户断开连接后触发ClientDisconnected事件
    /// </summary>
    void NotifyClientDisconnected(ENetPeer* disconnectedClient);

    /// <summary>
    /// 对当前总的连接客户进行计数
    /// </summary>
    int ConnectedClientsCount();
};
