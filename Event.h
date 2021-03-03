/*----------------------------------------------------------------*/
/* class Object   ��Ӧ�¼�������������Ǵ�Object��������          */
/*----------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>
class Object
{
};

/*----------------------------------------------------------------*/
/* class Event     ģ�����Ϊ �������� ����Ӧ������������         */
/* ��ʵ��һ���������¼���Ӧ����                                   */
/*----------------------------------------------------------------*/

template<typename rtnTtpe, typename ArgType>
class Event
{
    //ʹÿ���¼���������Ӧ�ĺ�������
#define EVENT_LIST_MAX_NUM  (10)
    typedef rtnTtpe(Object::* pMemFunc)(ArgType arg);

public:
    Event()
    {
        m_totalFunc = 0;
        m_obj = NULL;
        for (int i = 0; i < EVENT_LIST_MAX_NUM; i++)
        {
            m_func[i] = NULL;
        }
    }

    //�����ص���Ա����
    template <class _func_type>
    void associate(Object* obj, _func_type func)
    {
        m_obj = obj;
        m_func[m_totalFunc] = static_cast<pMemFunc> (func);
        m_totalFunc++;
    }
    //ɾ���¼������ص���Ա����
    template <class _func_type>
    void disAssociate(Object* obj, _func_type func)
    {
        if (obj != m_obj)
        {
            return;
        }

        //����
        for (int i = 0; i < m_totalFunc; i++)
        {
            if (m_func[i] == func)
            {
                break;
            }
        }

        //�ƶ�ɾ��
        for (int i=0; i < m_totalFunc - 1; i++)
        {
            m_func[i] = m_func[i + 1];
        }

        m_func[i] = NULL;
        m_totalFunc--;
    }

    //ִ�й����Ļص�����
    void sendEvent(ArgType arg)
    {
        for (int i = 0; i < m_totalFunc; i++)
        {
            if (m_func[i] != NULL)
            {
                ((m_obj->*pMemFunc(m_func[i])))(arg);
            }
        }
    }
private:
    Object* m_obj;
    pMemFunc m_func[EVENT_LIST_MAX_NUM];
    int m_totalFunc;
};