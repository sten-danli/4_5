//�������ݵı����������룺
//������Ϸ�������������Լ����������̣߳�
	//һ���߳��ֻ���������һ�����ִ�����ҷ����������������������д��һ�������С�
	//����һ���̴߳Ӷ�����ȡ����ҷ����������������Ȼ��ִ�������Ҫ�Ķ�����
//vector��list��list��vector��list��ƽ���İ�˳������ɾ������Ч�ʸߡ�vector������������ɾ������Ч�ʸߣ�

//׼���ó�Ա������Ϊ�̺߳����ķ�����д�߳�;//inMsgRecvQueue() //��������msgRecvQueue //outMsgRecvQueue()
//���뻰������ⷽ��������һ��c++������̱߳���������������ĵ�һ����"������"����ס����ʡ�
#include<iostream>
#include<list>
#include<thread>
#include<mutex>
using namespace std;

class A
{
public:
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; ++i)
		{
			mymutex.lock();
			cout << "inMsgRecvQueue()ִ�У�����Ԫ�أ�" << i << endl;
			msgRecvQueue.push_back(i);
			mymutex.unlock();
		}
			return;
	}
	
	bool feedback(int &command)
	{
		mymutex.lock();
		if (!msgRecvQueue.empty())
		{
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue()ִ�У�ȡ��Ԫ�أ�" << command << endl;
			mymutex.unlock();
			return true;
		}
		else
		{
			cout << "outMsgRecvQueue()��ʱû�����" << endl;
			mymutex.unlock();
			return false;
		}
	}

	void outMsgRecvQueue()
	{
		int command = 0;
		for (int i = 0; i < 100000; ++i)
		{
			if (feedback(command))
			{
				cout << "outMsgRecvQueue()ִ�У�ȡ��һ��Ԫ��" << command << endl;
				//Do something...
				//���Կ��ǽ������ݴ���
			}
			else
			{
				//��Ϣ����Ϊ��
				cout << "msgRecvQueue is in moments empty()." << endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int>msgRecvQueue;
	mutex mymutex;
};


int main()
{
	A myobj;
	thread inMsg(&A::inMsgRecvQueue, &myobj);
	thread outMsg(&A::outMsgRecvQueue, &myobj);
	inMsg.join();
	outMsg.join();

}