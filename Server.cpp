#include "Server.h"

/// <summary>
/// 将data广播给所有客户
/// </summary>
/// <param name="data"></param>
void Server::Broadcast(unsigned char* data, int len) {
    std::vector<ENetPeer*>* ret = _listeners->GetConnectedClients();
    for (int i = 0; i < ret->size(); i++)
    {
        ENetPacket* packet = enet_packet_create(data, len, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(ret[0][i], rand() % 256, packet);
    }
    delete(data);
}

// 当收到数据的时候所做的操作
void Server::DataReceived(Message* msg)
{
    PtMessagePackage* ptMessagePackage = PtMessagePackage::Read(msg->GetData(), msg->GetDataLen());
    // 缓存操作信息
    this->CacheClientInfo(ptMessagePackage);
    if (msg != NULL)
    {
        delete(msg);
        msg = NULL;
    }
}

// 客户端第一次连接，需要把id以及所有其他客户的操作发给它
void Server::ClientConnected(ENetPeer* peer)
{
    //Console.WriteLine("接收到新连接：" + client.GetRemoteAddress());
    // 生成客户的初始化信息
    unsigned char* playerPropertyData = NULL;
    int datalen = 0;
    this->ComputeInitProperty(playerPropertyData, &datalen);
    PtMessagePackage* package = PtMessagePackage::Build((int)S2CMessageType::ResponseClientConnected, playerPropertyData, datalen);
    unsigned char* byts = NULL;
    int bytslen = 0;
    PtMessagePackage::Write(package, byts, &bytslen);
    ENetPacket* packet = enet_packet_create(byts, bytslen, ENET_PACKET_FLAG_RELIABLE);//这里byts一定不要释放
    enet_peer_send(peer, rand() % 256, packet);
    if (package != NULL)
    {
        delete(package);
        package = NULL;
    }
    // 获取当前所有帧的操作发送给客户用以恢复
    std::vector<MutiData*>* totalOperations = this->GetAllOperations();
    for (int i = 0; i < totalOperations->size(); ++i) {
        MutiData* data = (*totalOperations)[i];
        unsigned char* mutidata = NULL;
        int mutilen = 0;
        MutiData::StructToBytes(data, mutidata, &mutilen);
        package = PtMessagePackage::Build((int)S2CMessageType::ResponseInitPlayer, mutidata, mutilen);
        unsigned char* byts2 = NULL;
        int bytslen2 = 0;
        PtMessagePackage::Write(package, byts2, &bytslen2);
        ENetPacket* packet2 = enet_packet_create(byts2, bytslen2, ENET_PACKET_FLAG_RELIABLE);//这里byts一定不要释放
        // 随机选择一个ENet通道进行发送
        enet_peer_send(peer, rand() % 256, packet2);
        if (package != NULL)
        {
            delete(package);
            package = NULL;
        }
    }
    package = PtMessagePackage::Build((int)S2CMessageType::ResponsePlayerReady, false, 0);
    unsigned char* byts3 = NULL;
    int bytslen3 = 0;
    PtMessagePackage::Write(package, byts3, &bytslen3);
    ENetPacket* packet3 = enet_packet_create(byts3, bytslen3, ENET_PACKET_FLAG_RELIABLE);//这里byts一定不要释放
    // 随机选择一个ENet通道进行发送
    enet_peer_send(peer, rand() % 256, packet3);
    if (package != NULL)
    {
        delete(package);
        package = NULL;
    }
}

// 当客户断开连接的时候所做的操作
void Server::ClientDisconnected(ENetPeer* peer)
{
    //Console.WriteLine("客户断开连接：" + msg.GetRemoteAddress());
    // 暂时不删除该客户的操作记录
}

Server::Server() {
    _listeners = new ServerListener();
}

Server::~Server() {
    if (_listeners != NULL)
        delete(_listeners);
}

/// <summary>
/// 服务器启动，自动设置绑定地址
/// </summary>
/// <param name="port">端口号</param>
void Server::Start(int port) {
    ENetAddress* address = new ENetAddress();
    address->host = ENET_HOST_ANY;
    address->port = port;
    Start(address, port);
}

/// <summary>
/// 服务器启动，手动设定绑定地址以及端口号
/// </summary>
/// <param name="ipAddress">地址</param>
/// <param name="port">端口号</param>
void Server::Start(ENetAddress* ipAddress, int port) {
    ServerListener* listener = new ServerListener(this, ipAddress, port);
    _listeners = listener;
}




// TODO 需要根据当前客户信息动态设置，目前是写死的
/// <summary>
/// 当客户刚连接上的时候需要发送客户一些信息，比如位置信息、旋转信息等等
/// </summary>
/// <returns></returns>
void Server::ComputeInitProperty(unsigned char* data, int* len) {
    GamePlayerSvo* player = GameServerData::AddNewPlayer();
    PlayerProperty* playerProperty = new PlayerProperty();
    //playerProperty->position = BitVector3::Zero();
    //playerProperty->x = BitFloat::Zero();
    //playerProperty->y = BitFloat::Zero();
    //playerProperty->z = BitFloat::Zero();
    playerProperty->x = 0;
    playerProperty->id = player->Id;
    playerProperty->sequence = GetCurrentSequence();
    playerProperty->readLoopIntervalMs = ServerListener::ReadLoopIntervalMs;
    StaticStructHelper::PropertyToBytes(playerProperty, data, len);
    delete(playerProperty);
}

/// <summary>
/// 获取所有的操作信息用以帮助客户端进行恢复
/// </summary>
/// <returns></returns>
std::vector<MutiData*>* Server::GetAllOperations() {
    std::vector<MutiData*>* data = new std::vector<MutiData*>;
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* tmp = _listeners->GetAllOperations();
    for (auto item : *tmp) {
        MutiData* muti = new MutiData();
        muti->sequence = item.first;
        for (int i = 0; i < item.second->size(); i++)
        {
            muti->totalClients.push_back((*item.second)[i]);
        }
        data->push_back(muti);
    }
    return data;
}

/// <summary>
/// 将数据包进行广播
/// </summary>
/// <param name="package"></param>
void Server::Broadcast(PtMessagePackage* package) {
    unsigned char* data = NULL;
    int len = 0;
    PtMessagePackage::Write(package, data, &len);
    Broadcast(data, len);
}

/// <summary>
/// 将客户发来的消息进行缓存
/// </summary>
/// <param name="message"></param>
void Server::CacheClientInfo(PtMessagePackage* message) {
    _listeners->CacheInfo(message);
}

/// <summary>
/// 获取当前服务器的帧号，因为目前只有一个listener，就直接取第一个
/// </summary>
/// <returns></returns>
unsigned int Server::GetCurrentSequence() {
    return _listeners->CurrentSequence();
}

/// <summary>
/// 当收到客户端发来的消息后，触发DataReceived事件
/// </summary>
/// <param name="client">发送消息的客户</param>
/// <param name="msg">发来的消息</param>
void Server::NotifyEndTransmissionRx(ENetPeer* client, unsigned char* msg, int len) {
    Message* m = new Message(client, msg, len);
    DataReceived(m);
}

/// <summary>
/// 当客户连接后触发ClientConnected事件
/// </summary>
void Server::NotifyClientConnected(ENetPeer* peer) {
    ClientConnected(peer);
}

/// <summary>
/// 当客户断开连接后触发ClientDisconnected事件
/// </summary>
void Server::NotifyClientDisconnected(ENetPeer* peer) {
    ClientDisconnected(peer);
}

/// <summary>
/// 对当前总的连接客户进行计数
/// </summary>
int Server::ConnectedClientsCount() {
    return _listeners->GetConnectedClientsCount();
}