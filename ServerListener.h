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
    // ENet中的服务器
    ENetHost* host = NULL;
    // 当前连接的所有客户
    std::vector<ENetPeer*>* _connectedClients = NULL;
    // 缓存每一帧的所有客户操作
    std::vector<SingleOperatorData*>* clientInfoBuffer = NULL; //后面加锁
    std::shared_timed_mutex clientInfoBuffer_mtx;//clientInfoBuffer的锁
    // 缓存自服务器开启以来的所有操作，key为帧号
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* allClientsOperation = NULL; //后面加锁
    std::shared_timed_mutex allClientsOperation_mtx;//allClientsOperation的锁
    std::shared_timed_mutex lockObj;
    //object lockObj = new object();  //锁 改！！！
    // 当前帧号
    unsigned int sequence = 0;
    ENetAddress* IPAddress = NULL;
    int Port;
    bool QueueStop;
    Server* _parent = NULL;

    void SetIPAddress(ENetAddress* address);

    void SetPort(int port);

    static void* ListenerLoop(void*);

    /// <summary>
    /// 每隔一个逻辑帧时间进行的一次操作：1、帧号加1；2、将这一帧的所有操作广播给客户
    /// </summary>
    /// <param name="state"></param>
    void AcceptAndSendToClients(int n); //n为了给timer固定格式用，没实质意义

    void Increment();

    /// <summary>
    /// 获取当前帧的所有操作再广播给其他客户
    /// </summary>
    /// <returns></returns>
    PtMessagePackage* GetMutiDataPackage();

    /// <summary>
    /// ENet的使用
    /// </summary>
    void RunLoopStep();

    bool CheckEvents(ENetEvent* event);

    void SetPingInterval(ENetPeer* peer, int interval);

    void SetTimeouts(ENetPeer* peer, int retryLimit, int retryMinimumTime, int maximumTime);

public:
    // 大约1秒10帧
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
    /// 将客户端发来的操作缓存下来
    /// </summary>
    /// <param name="message">操作数据</param>
    void CacheInfo(PtMessagePackage* message);

    /// <summary>
    /// 返回服务器当前缓存的所有操作
    /// </summary>
    /// <returns></returns>
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* GetAllOperations();

    unsigned int CurrentSequence();
};

