#include "thread_pool.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
CThreadPool threadpool(5);	//�̳߳ش�СΪ5

void CTask::setData(void* data) {
	m_ptrData = data;
}

void* CTask::getData() {
	return m_ptrData;
}

//��̬��Ա��ʼ��
vector<CTask*> CThreadPool::m_vecTaskList;
bool CThreadPool::shutdown = false;
pthread_mutex_t CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;

//�̹߳����๹�캯��
CThreadPool::CThreadPool(int threadNum) {
	this->m_iThreadNum = threadNum;
	//printf("I will create %d threads.\n", threadNum);
	Create();
}

//�̻߳ص�����
void* CThreadPool::ThreadFunc(void* threadData) {
	pthread_t tid = pthread_self();
	while (1)
	{
		pthread_mutex_lock(&m_pthreadMutex);
		//�������Ϊ�գ��ȴ�����������������
		while (m_vecTaskList.size() == 0 && !shutdown)
			pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);

		//�ر��߳�
		if (shutdown)
		{
			pthread_mutex_unlock(&m_pthreadMutex);
			//printf("[tid: %lu]\texit\n", pthread_self());
			pthread_exit(NULL);
		}

		//printf("[tid: %lu]\trun: ", tid);
		vector<CTask*>::iterator iter = m_vecTaskList.begin();
		//ȡ��һ�����񲢴���֮
		CTask* task = *iter;
		if (iter != m_vecTaskList.end())
		{
			task = *iter;
			m_vecTaskList.erase(iter);
		}

		pthread_mutex_unlock(&m_pthreadMutex);
		if (task->Run != NULL)
			(((ServerListener*)task->getData())->*(task->Run))();//��ĳ�Ա����ָ����ã��ȰѶ�������ã��ٽ�����ָ������ú��ɸö������
			//task->Run();	//ִ������
		//printf("[tid: %lu]\tidle\n", tid);

	}

	return (void*)0;
}

//�����������������񲢷����߳�ͬ���ź�
int CThreadPool::AddTask(CTask* task) {
	pthread_mutex_lock(&m_pthreadMutex);
	m_vecTaskList.push_back(task);
	pthread_mutex_unlock(&m_pthreadMutex);
	pthread_cond_signal(&m_pthreadCond);

	return 0;
}

//�����߳�
int CThreadPool::Create() {
	pthread_id = new pthread_t[m_iThreadNum];
	for (int i = 0; i < m_iThreadNum; i++)
		pthread_create(&pthread_id[i], NULL, ThreadFunc, NULL);

	return 0;
}

//ֹͣ�����߳�
int CThreadPool::StopAll() {
	//�����ظ�����
	if (shutdown)
		return -1;
	//printf("Now I will end all threads!\n\n");

	//�������еȴ����̣��̳߳�ҲҪ������
	shutdown = true;
	pthread_cond_broadcast(&m_pthreadCond);

	//�����ʬ
	for (int i = 0; i < m_iThreadNum; i++)
		pthread_join(pthread_id[i], NULL);

	delete[] pthread_id;
	pthread_id = NULL;

	//���ٻ���������������
	pthread_mutex_destroy(&m_pthreadMutex);
	pthread_cond_destroy(&m_pthreadCond);

	return 0;
}

//��ȡ��ǰ�����е�������
int CThreadPool::getTaskSize() {
	return m_vecTaskList.size();
}


class CMyTask : public CTask {
public:
	CMyTask() = default;
	
	~CMyTask() {}
};

void Run(void) {
	printf("haha\n");
	int x = rand() % 4 + 1;
	sleep(x);
	//return 0;
}

/*int main() {
	CMyTask taskObj;
	char szTmp[] = "hello!";
	taskObj.setData((void*)szTmp);
	taskObj.Run = &Run;

	for (int i = 0; i < 10; i++)
		threadpool.AddTask(&taskObj);

	while (1) {
		printf("There are still %d tasks need to handle\n", threadpool.getTaskSize());
		//���������û��������
		if (threadpool.getTaskSize() == 0) {
			//����̳߳�
			if (threadpool.StopAll() == -1) {
				printf("Thread pool clear, exit.\n");
				exit(0);
			}
		}
		sleep(2);
		printf("2 seconds later...\n");
	}
	return 0;
}*/