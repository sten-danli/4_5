//共享数据的保护案例代码：
//网络游戏服务器。两个自己创建的现线程：
	//一个线程手机玩家命令（用一个数字代表玩家发来的命令），并把命令数据写到一个队列中。
	//另外一个线程从队列中取出玩家发送来的命令，解析，然后执行玩家需要的动作；
//vector，list，list和vector。list：平凡的按顺序插入和删除数据效率高。vector容器随机插入和删除数据效率高；

//准备用成员函数作为线程函数的方法来写线程;//inMsgRecvQueue() //容器名：msgRecvQueue //outMsgRecvQueue()
//代码话解决问题方法：引用一个c++解决多线程保护共享数据问题的第一概念"互斥量"，记住这个词。
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
			cout << "inMsgRecvQueue()执行，插入元素：" << i << endl;
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
			cout << "outMsgRecvQueue()执行，取出元素：" << command << endl;
			mymutex.unlock();
			return true;
		}
		else
		{
			cout << "outMsgRecvQueue()暂时没有命令。" << endl;
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
				cout << "outMsgRecvQueue()执行，取出一个元素" << command << endl;
				//Do something...
				//可以考虑进行数据处理
			}
			else
			{
				//消息队列为空
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