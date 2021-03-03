/*----------------------------------------------------------------*/
/* class TestEvent                                                */
/*----------------------------------------------------------------*/
#include "Event.h"
#include "ByteBuffer.h"
using namespace std;
class TestEvent
{
public:
    void test()
    {
        //do somsthing
        //����

        //�����¼�
        //myEvent.sendEvent(100);
        //myEvent.sendEvent(200);
        myEvent.sendEvent();
    }
public:
    //�����¼�
    Event<bool, int> myEvent;
};

class TestEvent2
{
public:
    TestEvent2(ByteBuffer* b)
    {
        bytebuffer = b;
    }
    void test()
    {
        //do somsthing
        //����

        //�����¼�
        //myEvent.sendEvent(100);
        //myEvent.sendEvent(200);
        myEvent.sendEvent(bytebuffer);
    }
public:
    //�����¼�
    Event<bool, ByteBuffer*> myEvent;
    ByteBuffer* bytebuffer;
};

/*----------------------------------------------------------------*/
/* class TestClass                                                */
/*----------------------------------------------------------------*/
class TestClass :public Object
{
public:
    TestClass()
    {
        //�����¼�
        m_event.myEvent.associate(this, &TestClass::executeCb1);
        m_event.myEvent.associate(this, &TestClass::executeCb2);
    }

    //�¼���Ӧ����
    bool executeCb1(int result)
    {
        cout << "executeCb1 result = " << result << endl;
        return true;
    }
    //�¼���Ӧ����
    bool executeCb2(int result)
    {
        cout << "executeCb2 result = " << result << endl;
        return true;
    }

    void execute()
    {
        m_event.test();
    }
    void stop()
    {
        //ɾ���¼���������
        m_event.myEvent.disAssociate(this, &TestClass::executeCb1);
    }
private:
    TestEvent m_event;
};

//int main()
//{
//    TestClass testObj;
//
//    testObj.execute();
//    testObj.stop();
//    testObj.execute();
//
//    return 0;
//}

