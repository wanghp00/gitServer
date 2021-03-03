#pragma once
#include <vector>
#include <string>
#include <pthread.h>
//#include "Server.h"
using namespace std;
//extern CThreadPool threadpool;
/*ִ��������ࣺ�����������ݲ�ִ��*/
class CTask {
protected:
    string m_strTaskName;	//���������
    void* m_ptrData;	//Ҫִ�е�����ľ�������

public:
    CTask() = default;
    CTask(string& taskName) : m_strTaskName(taskName), m_ptrData(NULL) {}
    void (*Run)(void);
    void setData(void* data);	//������������
    void* getData();//��ȡ��������
    virtual ~CTask() {}

};

/*�̳߳ع�����*/
class CThreadPool {
private:
    static vector<CTask*> m_vecTaskList;	//�����б�
    static bool shutdown;	//�߳��˳���־
    int m_iThreadNum;	//�̳߳����������߳���
    pthread_t* pthread_id;

    static pthread_mutex_t m_pthreadMutex;	//�߳�ͬ����
    static pthread_cond_t m_pthreadCond;	//�߳�ͬ����������

protected:
    static void* ThreadFunc(void* threadData);	//���̵߳��̻߳ص�����
    static int MoveToIdle(pthread_t tid);	//�߳�ִ�н����󣬰��Լ���������߳���
    static int MoveToBusy(pthread_t tid);	//���뵽æµ�߳���ȥ
    int Create();	//�����̳߳��е��߳�

public:
    CThreadPool(int threadNum);
    int AddTask(CTask* task);	//��������ӵ����������
    int StopAll();	//ʹ�̳߳��е������߳��˳�
    int getTaskSize();	//��ȡ��ǰ��������е�������
};