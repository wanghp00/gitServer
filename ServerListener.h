#pragma once
#include <enet/enet.h>
#include "NetStruct.h"
#include "PtMessagePackage.h"
#include "MessageEnum.h"
#include <vector>
#include <map>
#include <memory>
#include <shared_mutex>
#include <unistd.h>
#include <pthread.h>
//#include "Server.h"
//#include "timer.h"
//#include "thread_pool.h"
class Server;
class ServerListener {
private:
    // ENet�еķ�����
    ENetHost* host = NULL;
    // ��ǰ���ӵ����пͻ�
    std::vector<ENetPeer*>* _connectedClients = NULL;
    // ����ÿһ֡�����пͻ�����
    std::vector<SingleOperatorData*>* clientInfoBuffer = NULL; //�������
    std::shared_timed_mutex clientInfoBuffer_mtx;//clientInfoBuffer����
    // �����Է������������������в�����keyΪ֡��
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* allClientsOperation = NULL; //�������
    std::shared_timed_mutex allClientsOperation_mtx;//allClientsOperation����
    std::shared_timed_mutex lockObj;
    //object lockObj = new object();  //�� �ģ�����
    // ��ǰ֡��
    unsigned int sequence = 0;
    ENetAddress* IPAddress = NULL;
    int Port;
    bool QueueStop;
    Server* _parent = NULL;

    void SetIPAddress(ENetAddress* address);

    void SetPort(int port);

    static void* ListenerLoop(void*);

    /// <summary>
    /// ÿ��һ���߼�֡ʱ����е�һ�β�����1��֡�ż�1��2������һ֡�����в����㲥���ͻ�
    /// </summary>
    /// <param name="state"></param>
    void AcceptAndSendToClients(int n); //nΪ�˸�timer�̶���ʽ�ã�ûʵ������

    void Increment();

    /// <summary>
    /// ��ȡ��ǰ֡�����в����ٹ㲥�������ͻ�
    /// </summary>
    /// <returns></returns>
    PtMessagePackage* GetMutiDataPackage();

    /// <summary>
    /// ENet��ʹ��
    /// </summary>
    void RunLoopStep();

    bool CheckEvents(ENetEvent* event);

    void SetPingInterval(ENetPeer* peer, int interval);

    void SetTimeouts(ENetPeer* peer, int retryLimit, int retryMinimumTime, int maximumTime);

public:
    // ��Լ1��10֡
    static const unsigned int ReadLoopIntervalMs = 100;

    ServerListener();

    ServerListener(Server* server, ENetAddress* ipaddress, int port);
    
    ~ServerListener();

    int GetConnectedClientsCount();

    std::vector<ENetPeer*>* GetConnectedClients();

    ENetHost* GetListener();

    bool GetQueueStop();

    void SetQueueStop(bool b);

    ENetAddress* GetIPAddress();

    int GetPort();

    /// <summary>
    /// ���ͻ��˷����Ĳ�����������
    /// </summary>
    /// <param name="message">��������</param>
    void CacheInfo(PtMessagePackage* message);

    /// <summary>
    /// ���ط�������ǰ��������в���
    /// </summary>
    /// <returns></returns>
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* GetAllOperations();

    unsigned int CurrentSequence();
};

