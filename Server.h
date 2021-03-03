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
    // һ��Server��������ж��ServerListener��Ŀǰֻ��һ��
    //std::vector<ServerListener*> _listeners;
    ServerListener* _listeners = NULL;
    //std::vector<SingleOperatorData*> allClientsOperation;

    /// <summary>
    /// ��data�㲥�����пͻ�
    /// </summary>
    /// <param name="data"></param>
    void Broadcast(unsigned char* data, int len);
    void DataReceived(Message* msg);
    void ClientConnected(ENetPeer* peer);
    void ClientDisconnected(ENetPeer* peer);
public:
    // ���ͻ������ϵ�ʱ����Ҫִ�е��¼�
    //event EventHandler<Peer> ClientConnected;
    // ���ͻ���ʧȥ���ӵ�ʱ����Ҫִ�е��¼�
    //event EventHandler<Peer> ClientDisconnected;
    // ���ͻ��˷�����Ϣ��ʱ����Ҫִ�е��¼�
    //event EventHandler<Message> DataReceived;

    Server();

    ~Server();

    /// <summary>
    /// �������������Զ����ð󶨵�ַ
    /// </summary>
    /// <param name="port">�˿ں�</param>
    void Start(int port);

    /// <summary>
    /// �������������ֶ��趨�󶨵�ַ�Լ��˿ں�
    /// </summary>
    /// <param name="ipAddress">��ַ</param>
    /// <param name="port">�˿ں�</param>
    void Start(ENetAddress* ipAddress, int port);

    // TODO ��Ҫ���ݵ�ǰ�ͻ���Ϣ��̬���ã�Ŀǰ��д����
    /// <summary>
    /// ���ͻ��������ϵ�ʱ����Ҫ���Ϳͻ�һЩ��Ϣ������λ����Ϣ����ת��Ϣ�ȵ�
    /// </summary>
    /// <returns></returns>
    void ComputeInitProperty(unsigned char* data, int* len);

    /// <summary>
    /// ��ȡ���еĲ�����Ϣ���԰����ͻ��˽��лָ�
    /// </summary>
    /// <returns></returns>
    std::vector<MutiData*>* GetAllOperations();
        
    /// <summary>
    /// �����ݰ����й㲥
    /// </summary>
    /// <param name="package"></param>
    void Broadcast(PtMessagePackage* package);

    /// <summary>
    /// ���ͻ���������Ϣ���л���
    /// </summary>
    /// <param name="message"></param>
    void CacheClientInfo(PtMessagePackage* message);

    /// <summary>
    /// ��ȡ��ǰ��������֡�ţ���ΪĿǰֻ��һ��listener����ֱ��ȡ��һ��
    /// </summary>
    /// <returns></returns>
    unsigned int GetCurrentSequence();

    /// <summary>
    /// ���յ��ͻ��˷�������Ϣ�󣬴���DataReceived�¼�
    /// </summary>
    /// <param name="client">������Ϣ�Ŀͻ�</param>
    /// <param name="msg">��������Ϣ</param>
    void NotifyEndTransmissionRx(ENetPeer* client, unsigned char* msg, int len);

    /// <summary>
    /// ���ͻ����Ӻ󴥷�ClientConnected�¼�
    /// </summary>
    void NotifyClientConnected(ENetPeer* newClient);

    /// <summary>
    /// ���ͻ��Ͽ����Ӻ󴥷�ClientDisconnected�¼�
    /// </summary>
    void NotifyClientDisconnected(ENetPeer* disconnectedClient);

    /// <summary>
    /// �Ե�ǰ�ܵ����ӿͻ����м���
    /// </summary>
    int ConnectedClientsCount();
};
