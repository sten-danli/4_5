#include<iostream>
#include<vector>
#include<thread>
#include<list>
#include<mutex>
using namespace std;

#if 0
//һ��Ҫ��ס�õ���������������̵߳Ļ����ַ���
void myprint( int inum)
{
	for (int i = 0;  i < 10; ++i)
	{
		cout << "myprint()�߳̿�ʼִ����,�̱߳�ţ�" << inum << endl;
	}
	
	//cout << "myprint()�߳̿�ʼִ����,�̱߳�ţ�" << inum << endl;
	////Do Somthing...
	//cout << "myprint()�߳̿�������,	 �̱߳�ţ�" << inum << endl;

}
int main()
{//����һ��ר�Ŵ洢�̵߳�������
	vector<thread>mythreads;
//����10���̣߳��߳����ͳһ��myprint��ÿ���߳��Լ�ִ���Լ�����Ӱ�졣
	for (int i = 0; i < 10; i++)
	{
		mythreads.push_back(thread(myprint, i));//����10���߳�//��thread��ʱ����ŵ�mythread��������ȥ���й������������������һ��thread��������飬
							//���ֹ�����������һ�δ����������̣߳�������Щ�����߳̽��й������ܷ��㡣�������ǾͿ�����iter����������ÿһ���̶߳���ȡ������
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)//�������ǾͿ�����iter����������ÿһ���̶߳���ȡ������
	{
		iter->join();//Ȼ���������join��Ա�����ȴ��̵߳�ִ����ϡ�
		
	}
	cout << "i love c++" << endl;//���ִ����䣬���������˳�
	return 0;
}
#endif // 0

#if 0
//��.���ݹ������
//(2.1)ֻ���������ǰ�ȫ�ȶ��ģ�����Ҫʲô�����ֶΡ�ֱ�Ӷ��Ϳ��ԣ�
//(2.2)�ж���д;2���߳�д��8���̶߳��������û���ر����ѩ�϶�������
//��򵥵Ĳ�������������ʱ����д��д��ʱ���ܶ���2���̲߳���ͬʱд��8���̲߳���ͬʱ����
//д�Ķ�����10С�������������л����¸��ֹ����¼�������������

vector<int>g_v = { 1,2,3 };//��������//��Ϊ���Ǹ�ȫ�ֱ�����ÿ���̶߳�����������
void myprint(int inum)
{
	for (int i=0;i<g_v.size();++i)
	{
		cout << g_v[i] << endl;
	}
}

int main()
{
		vector<thread>mythreads;
		for (int i = 0; i < 10; i++)
		{
			mythreads.push_back(thread(myprint, i));
		}

		for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)
		{
			iter->join();
		}
		cout << "i love c++" << endl;
		return 0;

}

#endif // 0

//�����������ݵı����������룺
//������Ϸ�������������Լ����������̣߳�
	//һ���߳��ֻ���������һ�����ִ�����ҷ����������������������д��һ�������С�
	//����һ���̴߳Ӷ�����ȡ����ҷ����������������Ȼ��ִ�������Ҫ�Ķ�����
//vector��list��list��vector��list��ƽ���İ�˳������ɾ������Ч�ʸߡ�vector������������ɾ������Ч�ʸߣ�

//׼���ó�Ա������Ϊ�̺߳����ķ�����д�߳�;//inMsgRecvQueue() //��������msgRecvQueue //outMsgRecvQueue()
//���뻰������ⷽ��������һ��c++������̱߳���������������ĵ�һ����"������"����ס����ʡ�

#if 0
class A
{
public:
	void inMsgRecvQuue()//�߳�һ
	{
		for (int i = 0; i < 100000; ++i)
		{
			cout << "inMsgRecvQueue()ִ�У�����Ԫ�أ�" << i << endl;
			msgRecvQueue.push_back(i);//�����������i�������յ��������ֱ��Ū����Ϣ�����������
		}
	}

	//�����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecvQueue()//�̶߳�
	{
		for (int i = 0; i < 100000; ++i)
		{
			if (!msgRecvQueue.empty())
			{
				int command = msgRecvQueue.front();
				msgRecvQueue.pop_front();
				cout << "outMsgRecvQueue()ִ�У�ȡ��Ԫ�أ�" << command << endl;
			}
			else
			{
				cout << "outMsgRecvQueue()��ʱû�����" << endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int>msgRecvQueue;//�������������ڴ�����Ҹ����Ƿ��͹��������
	mutex mymutex;
};


int main()
{
	A myobj;
	thread inMsg(&A::inMsgRecvQuue, &myobj);//�ڶ����������ã����ܱ�֤�̳߳����õ���ͬһ������
	thread outMsg(&A::outMsgRecvQueue, &myobj);
	inMsg.join();
	outMsg.join();


}
#endif // 0

#if 0
class A
{
public:
	void inMsgRecvQuue()//�߳�һ
	{
		for (int i = 0; i < 100000; ++i)
		{

			cout << "inMsgRecvQueue()ִ�У�����Ԫ�أ�" << i << endl;
			mymutex.lock();
			msgRecvQueue.push_back(i);//�����������i�������յ��������ֱ��Ū����Ϣ�����������
			mymutex.unlock();
		}
	}

	bool feedback(int &command)
	{
		
		mymutex.lock();
		if (!msgRecvQueue.empty())
		{
			//��Ϣ��Ϊ��
			 command = msgRecvQueue.front();//���ص�һ��Ԫ�أ��������Ԫ���Ƿ���ڣ�
			msgRecvQueue.pop_front();//�Ƴ���һ��Ԫ�أ��������ء�
			mymutex.unlock();
			return true;
		}
		mymutex.unlock();
		return false;
	}

	//�����ݴ���Ϣ������ȡ�����߳�
	void outMsgRecvQueue()//�̶߳�
	{
		int command = 0;
		for (int i = 0; i < 100000; ++i)
		{
			bool result = feedback(command);
			if (result == true)
			{
				cout << "outMsgRecvQueue()ִ�У�ȡ��һ��Ԫ��"  <<command<< endl;
				//Do somthing...
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
	list<int>msgRecvQueue;//�������������ڴ�����Ҹ����Ƿ��͹��������
	mutex mymutex;
};


int main()
{
	A myobj;
	thread inMsg(&A::inMsgRecvQuue, &myobj);//�ڶ����������ã����ܱ�֤�̳߳����õ���ͬһ������
	thread outMsg(&A::outMsgRecvQueue,&myobj);
	inMsg.join();
	outMsg.join();
}
#endif // 0

class A
{
public: 
	void inMsgQueue()
	{
		for (int i = 0; i < 1000; ++i)
		{
			
			cout << "inMsgRecvQueue()ִ�У�����Ԫ�أ�" <<i<< endl;
			
		//�ܽ᣺std::lock();һ���������������������ʹ�ã�����һ��һ��������
		//mymutex1.lock();//����1//��ȫ�ֶ�lock() & unloc();
		//mymutex2.lock();

		//std::lock_guard<std::mutex>mutex_gard1(mymutex11);//����2//�����Զ�unlock()�����ǲ��ܽ�������������Ƿ������˷���4�������Զ�����������������Լ����unlock()���⣻
		//std::lock_guard<std::mutex>mutex_gard2(mymutex12);
	
		//std::lock(mymutex1, mymutex2);//����3//�ź����ǲ����Զ�unlock();

			std::lock(mymutex1, mymutex2);//����4,����Ҫ�ͷ�����һ���ã�����д�÷���3�������Զ�����������������Լ����unlock()���⣻
			std::lock_guard<std::mutex>guard1(mymutex1, std::adopt_lock);
			std::lock_guard<std::mutex>guard2(mymutex2, std::adopt_lock);

			MsgRecvQueue.push_back(i);
			//mymutex1.unlock();
			//mymutex2.unlock();
		}
		return;
	}
	bool outMsgLULProc(int &commando)
	{
		//std::lock_guard<std::mutex>mutex_gard1(mymutex11);
		//std::lock_guard<std::mutex>mutex_gard2(mymutex12);
		mymutex1.lock();
		mymutex2.lock();
	
		if (!MsgRecvQueue.empty())
		{
			commando = MsgRecvQueue.front();
			MsgRecvQueue.pop_front();
			mymutex1.unlock();
			mymutex2.unlock();
			return true;
		}
		else
		{
			mymutex1.unlock();
			mymutex2.unlock();
			return false;
		}
	}
	void outMsgQueue()
	{
		int commando = 0;
		for (int i = 0; i < 1000; ++i)
		{
			bool result = outMsgLULProc(commando);
			if (result == true)
			{
				cout << "outMsgRecvQueue()ִ�У�ȡ��һ��Ԫ��" << commando << endl;
				//Do something...
				//���Կ��ǽ������ݴ���
			}
			else
			{
				cout << "msgRecvQueue is in moments empty()." << endl;
			}
		}
		cout << "end!" << endl;
	}
private:
	list<int>MsgRecvQueue;
	mutex mymutex1;
	mutex mymutex2;
};
int main()
{
	A mobj;
	thread inMsg(&A::inMsgQueue, &mobj);
	thread outMsg(&A::outMsgQueue, &mobj);
	inMsg.join();
	outMsg.join();
}