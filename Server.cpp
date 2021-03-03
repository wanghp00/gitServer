#include "Server.h"

/// <summary>
/// ��data�㲥�����пͻ�
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

// ���յ����ݵ�ʱ�������Ĳ���
void Server::DataReceived(Message* msg)
{
    PtMessagePackage* ptMessagePackage = PtMessagePackage::Read(msg->GetData(), msg->GetDataLen());
    // ���������Ϣ
    this->CacheClientInfo(ptMessagePackage);
    if (msg != NULL)
    {
        delete(msg);
        msg = NULL;
    }
}

// �ͻ��˵�һ�����ӣ���Ҫ��id�Լ����������ͻ��Ĳ���������
void Server::ClientConnected(ENetPeer* peer)
{
    //Console.WriteLine("���յ������ӣ�" + client.GetRemoteAddress());
    // ���ɿͻ��ĳ�ʼ����Ϣ
    unsigned char* playerPropertyData = NULL;
    int datalen = 0;
    this->ComputeInitProperty(playerPropertyData, &datalen);
    PtMessagePackage* package = PtMessagePackage::Build((int)S2CMessageType::ResponseClientConnected, playerPropertyData, datalen);
    unsigned char* byts = NULL;
    int bytslen = 0;
    PtMessagePackage::Write(package, byts, &bytslen);
    ENetPacket* packet = enet_packet_create(byts, bytslen, ENET_PACKET_FLAG_RELIABLE);//����bytsһ����Ҫ�ͷ�
    enet_peer_send(peer, rand() % 256, packet);
    if (package != NULL)
    {
        delete(package);
        package = NULL;
    }
    // ��ȡ��ǰ����֡�Ĳ������͸��ͻ����Իָ�
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
        ENetPacket* packet2 = enet_packet_create(byts2, bytslen2, ENET_PACKET_FLAG_RELIABLE);//����bytsһ����Ҫ�ͷ�
        // ���ѡ��һ��ENetͨ�����з���
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
    ENetPacket* packet3 = enet_packet_create(byts3, bytslen3, ENET_PACKET_FLAG_RELIABLE);//����bytsһ����Ҫ�ͷ�
    // ���ѡ��һ��ENetͨ�����з���
    enet_peer_send(peer, rand() % 256, packet3);
    if (package != NULL)
    {
        delete(package);
        package = NULL;
    }
}

// ���ͻ��Ͽ����ӵ�ʱ�������Ĳ���
void Server::ClientDisconnected(ENetPeer* peer)
{
    //Console.WriteLine("�ͻ��Ͽ����ӣ�" + msg.GetRemoteAddress());
    // ��ʱ��ɾ���ÿͻ��Ĳ�����¼
}

Server::Server() {
    _listeners = new ServerListener();
}

Server::~Server() {
    if (_listeners != NULL)
        delete(_listeners);
}

/// <summary>
/// �������������Զ����ð󶨵�ַ
/// </summary>
/// <param name="port">�˿ں�</param>
void Server::Start(int port) {
    ENetAddress* address = new ENetAddress();
    address->host = ENET_HOST_ANY;
    address->port = port;
    Start(address, port);
}

/// <summary>
/// �������������ֶ��趨�󶨵�ַ�Լ��˿ں�
/// </summary>
/// <param name="ipAddress">��ַ</param>
/// <param name="port">�˿ں�</param>
void Server::Start(ENetAddress* ipAddress, int port) {
    ServerListener* listener = new ServerListener(this, ipAddress, port);
    _listeners = listener;
}




// TODO ��Ҫ���ݵ�ǰ�ͻ���Ϣ��̬���ã�Ŀǰ��д����
/// <summary>
/// ���ͻ��������ϵ�ʱ����Ҫ���Ϳͻ�һЩ��Ϣ������λ����Ϣ����ת��Ϣ�ȵ�
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
/// ��ȡ���еĲ�����Ϣ���԰����ͻ��˽��лָ�
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
/// �����ݰ����й㲥
/// </summary>
/// <param name="package"></param>
void Server::Broadcast(PtMessagePackage* package) {
    unsigned char* data = NULL;
    int len = 0;
    PtMessagePackage::Write(package, data, &len);
    Broadcast(data, len);
}

/// <summary>
/// ���ͻ���������Ϣ���л���
/// </summary>
/// <param name="message"></param>
void Server::CacheClientInfo(PtMessagePackage* message) {
    _listeners->CacheInfo(message);
}

/// <summary>
/// ��ȡ��ǰ��������֡�ţ���ΪĿǰֻ��һ��listener����ֱ��ȡ��һ��
/// </summary>
/// <returns></returns>
unsigned int Server::GetCurrentSequence() {
    return _listeners->CurrentSequence();
}

/// <summary>
/// ���յ��ͻ��˷�������Ϣ�󣬴���DataReceived�¼�
/// </summary>
/// <param name="client">������Ϣ�Ŀͻ�</param>
/// <param name="msg">��������Ϣ</param>
void Server::NotifyEndTransmissionRx(ENetPeer* client, unsigned char* msg, int len) {
    Message* m = new Message(client, msg, len);
    DataReceived(m);
}

/// <summary>
/// ���ͻ����Ӻ󴥷�ClientConnected�¼�
/// </summary>
void Server::NotifyClientConnected(ENetPeer* peer) {
    ClientConnected(peer);
}

/// <summary>
/// ���ͻ��Ͽ����Ӻ󴥷�ClientDisconnected�¼�
/// </summary>
void Server::NotifyClientDisconnected(ENetPeer* peer) {
    ClientDisconnected(peer);
}

/// <summary>
/// �Ե�ǰ�ܵ����ӿͻ����м���
/// </summary>
int Server::ConnectedClientsCount() {
    return _listeners->GetConnectedClientsCount();
}