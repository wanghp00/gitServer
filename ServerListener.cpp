#include "Server.h"

void ServerListener::SetIPAddress(ENetAddress* address)
{
    IPAddress = address;
}

void ServerListener::SetPort(int port)
{
    Port = port;
}

void* ServerListener::ListenerLoop(void* sl) {
    // 每隔一段时间执行一次发送消息的操作 还没换为c++代码
    /*Timer timer(0, ReadLoopIntervalMs * 1000);
    ProcessHandler Handler = &ServerListener::AcceptAndSendToClients;
    timer.setHandler(this->Handler);
    timer.reset();*/
    ServerListener* s = (ServerListener*)sl;
    while (!(s->QueueStop)) {
        // 循环接收客户端发来的消息
        s->RunLoopStep();
    }
    // 当关闭服务器的时候释放资源
    //timer.Dispose();
}

/// <summary>
/// 每隔一个逻辑帧时间进行的一次操作：1、帧号加1；2、将这一帧的所有操作广播给客户
/// </summary>
/// <param name="state"></param>
void ServerListener::AcceptAndSendToClients(int n) {
    Increment();
    _parent->Broadcast(GetMutiDataPackage());
}

void ServerListener::Increment() {
    std::unique_lock<std::shared_timed_mutex> lock(lockObj);
    sequence++;
}

/// <summary>
/// 获取当前帧的所有操作再广播给其他客户
/// </summary>
/// <returns></returns>
PtMessagePackage* ServerListener::GetMutiDataPackage() {
    std::unique_lock<std::shared_timed_mutex> lock(clientInfoBuffer_mtx);
    std::vector<SingleOperatorData*>* singleOperatorDatas(clientInfoBuffer);
    clientInfoBuffer->clear();
    // 设置当前帧序列
    for (int i = 0; i < singleOperatorDatas->size(); i++)
    {
        (*singleOperatorDatas)[i]->sequence = sequence;
    }

    MutiData* data = new MutiData();
    data->sequence = sequence;
    data->totalClients.assign(singleOperatorDatas->begin(), singleOperatorDatas->end());
    unsigned char* ret = NULL;
    int retlen = 0;
    MutiData::StructToBytes(data, ret, &retlen);
    PtMessagePackage* ptMessagePackage = PtMessagePackage::Build((int)S2CMessageType::ResponseSyncKeyframes, ret, retlen);
    if (data != NULL)
        delete(data);
    if (singleOperatorDatas != NULL)
    {
        for (int i = 0; i < singleOperatorDatas->size(); i++)
        {
            delete((*singleOperatorDatas)[i]);
        }
        delete(singleOperatorDatas);
    }
    if(ret!=NULL)
        free(ret);
    return ptMessagePackage;
}

/// <summary>
/// ENet的使用
/// </summary>
void ServerListener::RunLoopStep() {
    if (host == NULL)
        return;
    ENetEvent _event;
    if (enet_host_service(host, &_event, 10) > 0) {
        do {
            ENetPeer* peer = _event.peer;
            switch (_event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                // If you are using ENet 1.3.4 or newer, the following two methods will work:
                enet_peer_ping_interval(peer, 1000);
                enet_peer_timeout(peer, 8, 5000, 60000);
                if(_connectedClients!=NULL)
                _connectedClients->push_back(peer);
                _parent->NotifyClientConnected(peer);  
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                _parent->NotifyEndTransmissionRx(peer, _event.packet->data, _event.packet->dataLength);
                enet_packet_destroy(_event.packet);//因为上面复制了data的数据开辟了新的内存,所以旧的要释放
                //_event.Packet.Dispose();
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::vector<ENetPeer*>::iterator it;
                for (it = _connectedClients->begin(); it != _connectedClients->end();)
                {
                    if (*it == peer)
                        it = _connectedClients->erase(it);
                    else
                        it++;
                }
                _parent->NotifyClientDisconnected(peer);
                break;
            }
        } while (enet_host_check_events(host, &_event)>0);
    }
}

bool ServerListener::CheckEvents(ENetEvent* event)
{
    if (host == NULL)
    {
        //print log
        return false;
    }
    int ret = enet_host_check_events(host, event);
    if (ret < 0) { //print("Error while checking for events."); 
    }
    if (ret == 0) { return false; }
    return true;
}

void ServerListener::SetPingInterval(ENetPeer* peer, int interval)
{
    if (peer == NULL)
    {
        //print log
        return;
    }
    enet_peer_ping_interval(peer, (unsigned int)interval);
}

void ServerListener::SetTimeouts(ENetPeer* peer, int retryLimit, int retryMinimumTime, int maximumTime)
{
    if (peer == NULL)
    {
        //print log
        return;
    }
    if (retryLimit < 0 || retryLimit > 20) { //log("retryLimit"); 
    }
    if (retryMinimumTime < 0) { //log("retryMinimumTime"); 
    }
    if (maximumTime < 0) { //log("maximumTime"); 
    }
    enet_peer_timeout(peer, 1U << retryLimit, (unsigned int)retryMinimumTime, (unsigned int)maximumTime);
}

ServerListener::ServerListener()
{
    _connectedClients = new std::vector<ENetPeer*>();
    clientInfoBuffer = new std::vector<SingleOperatorData*>();
    allClientsOperation = new std::map<unsigned int, std::vector<SingleOperatorData*>*>();
}

ServerListener::~ServerListener()
{
    if (_connectedClients != NULL)
        delete(_connectedClients);
    if (clientInfoBuffer != NULL)
        delete(clientInfoBuffer);
    if (allClientsOperation != NULL)
        delete(allClientsOperation);
    if (host != NULL)
        enet_host_destroy(host);
}


int ServerListener::GetConnectedClientsCount()
{
    return _connectedClients->size();
}

std::vector<ENetPeer*>* ServerListener::GetConnectedClients()
{
    return _connectedClients;
}

ENetHost* ServerListener::GetListener()
{
    return host;
}

bool ServerListener::GetQueueStop()
{
    return QueueStop;
}

void ServerListener::SetQueueStop(bool b)
{
    QueueStop = b;
}

ENetAddress* ServerListener::GetIPAddress()
{
    return IPAddress;
}

int ServerListener::GetPort()
{
    return Port;
}

ServerListener::ServerListener(Server* server, ENetAddress* ipaddress, int port) {
    SetQueueStop(false);
    _parent = server;
    IPAddress = ipaddress;
    SetPort(port);
    host = enet_host_create(ipaddress, 32, 1, 0, 0);
    pthread_t th;
    pthread_create(&th, NULL, &ServerListener::ListenerLoop, this);
}

/// <summary>
/// 将客户端发来的操作缓存下来
/// </summary>
/// <param name="message">操作数据</param>
void ServerListener::CacheInfo(PtMessagePackage* message) {
    SingleOperatorData* single = StaticStructHelper::BytesToSingle(message->m_Content, message->content_len);
    {
        std::unique_lock<std::shared_timed_mutex> lock(clientInfoBuffer_mtx);
        clientInfoBuffer->push_back(single);
    }
    {
        std::unique_lock<std::shared_timed_mutex> lock(allClientsOperation_mtx);
        std::map<unsigned int, std::vector<SingleOperatorData*>*>::iterator iter;
        iter = allClientsOperation->find(single->sequence);
        if (iter != allClientsOperation->end())//找到该内容
        {
            (*allClientsOperation)[single->sequence]->push_back(single);
        }
        else
        {
            std::vector<SingleOperatorData*>* tmp = new std::vector<SingleOperatorData*>();
            tmp->push_back(single);
            (*allClientsOperation)[single->sequence] = tmp;
        }
    }
    if (message != NULL)
        delete(message);
}

/// <summary>
/// 返回服务器当前缓存的所有操作
/// </summary>
/// <returns></returns>
std::map<unsigned int, std::vector<SingleOperatorData*>*>* ServerListener::GetAllOperations()
{
    std::shared_lock<std::shared_timed_mutex> lock(allClientsOperation_mtx);
    std::map<unsigned int, std::vector<SingleOperatorData*>*>* tmp = new std::map<unsigned int, std::vector<SingleOperatorData*>*>();
    for (auto x : *allClientsOperation)
    {
        (*tmp)[x.first] = x.second;
    }
    return tmp;
}

unsigned int ServerListener::CurrentSequence()
{
    std::shared_lock<std::shared_timed_mutex> lock(lockObj);
    return sequence;
}