#include<iostream>
#include<vector>
#include<thread>
#include<list>
#include<mutex>
using namespace std;

#if 0
//一：要记住用迭代器来创建多个线程的基本手法；
void myprint( int inum)
{
	for (int i = 0;  i < 10; ++i)
	{
		cout << "myprint()线程开始执行了,线程编号：" << inum << endl;
	}
	
	//cout << "myprint()线程开始执行了,线程编号：" << inum << endl;
	////Do Somthing...
	//cout << "myprint()线程开结束了,	 线程编号：" << inum << endl;

}
int main()
{//创建一个专门存储线程的容器；
	vector<thread>mythreads;
//创建10个线程，线程入口统一用myprint，每个线程自己执行自己互不影响。
	for (int i = 0; i < 10; i++)
	{
		mythreads.push_back(thread(myprint, i));//创建10个线程//把thread临时对象放到mythread容器当中去进行管理，这个容器看起来像一个thread对象的数组，
							//这种管理方法对我们一次创建大量的线程，并对这些大量线程进行管理他很方便。后续我们就可以用iter迭代器来把每一个线程对象取出来。
	}
	for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter)//后续我们就可以用iter迭代器来把每一个线程对象取出来。
	{
		iter->join();//然后调用他的join成员函数等待线程的执行完毕。
		
	}
	cout << "i love c++" << endl;//最后执行这句，整个进程退出
	return 0;
}
#endif // 0

#if 0
//二.数据共享分析
//(2.1)只读的数据是安全稳定的，不需要什么处理手段。直接读就可以；
//(2.2)有读有写;2个线程写，8各线程都如果代码没有特别处理成雪肯定崩溃；
//最简单的不崩溃处理，读的时候不能写，写的时候不能读，2个线程不能同时写，8个线程不能同时都。
//写的动作分10小步；由于任务切换导致各种诡异事件发生，崩溃。

vector<int>g_v = { 1,2,3 };//共享数据//因为他是个全局变量，每个线程都可以来读，
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

//三：共享数据的保护案例代码：
//网络游戏服务器。两个自己创建的现线程：
	//一个线程手机玩家命令（用一个数字代表玩家发来的命令），并把命令数据写到一个队列中。
	//另外一个线程从队列中取出玩家发送来的命令，解析，然后执行玩家需要的动作；
//vector，list，list和vector。list：平凡的按顺序插入和删除数据效率高。vector容器随机插入和删除数据效率高；

//准备用成员函数作为线程函数的方法来写线程;//inMsgRecvQueue() //容器名：msgRecvQueue //outMsgRecvQueue()
//代码话解决问题方法：引用一个c++解决多线程保护共享数据问题的第一概念"互斥量"，记住这个词。

#if 0
class A
{
public:
	void inMsgRecvQuue()//线程一
	{
		for (int i = 0; i < 100000; ++i)
		{
			cout << "inMsgRecvQueue()执行，插入元素：" << i << endl;
			msgRecvQueue.push_back(i);//假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；
		}
	}

	//把数据从消息队列中取出的线程
	void outMsgRecvQueue()//线程二
	{
		for (int i = 0; i < 100000; ++i)
		{
			if (!msgRecvQueue.empty())
			{
				int command = msgRecvQueue.front();
				msgRecvQueue.pop_front();
				cout << "outMsgRecvQueue()执行，取出元素：" << command << endl;
			}
			else
			{
				cout << "outMsgRecvQueue()暂时没有命令。" << endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int>msgRecvQueue;//容器，串门用于代表玩家给咱们发送过来的命令。
	mutex mymutex;
};


int main()
{
	A myobj;
	thread inMsg(&A::inMsgRecvQuue, &myobj);//第二参数是引用，才能保证线程城里用的是同一个对象。
	thread outMsg(&A::outMsgRecvQueue, &myobj);
	inMsg.join();
	outMsg.join();


}
#endif // 0

#if 0
class A
{
public:
	void inMsgRecvQuue()//线程一
	{
		for (int i = 0; i < 100000; ++i)
		{

			cout << "inMsgRecvQueue()执行，插入元素：" << i << endl;
			mymutex.lock();
			msgRecvQueue.push_back(i);//假设这个数字i就是我收到的命令，我直接弄到消息队列里边来；
			mymutex.unlock();
		}
	}

	bool feedback(int &command)
	{
		
		mymutex.lock();
		if (!msgRecvQueue.empty())
		{
			//消息不为空
			 command = msgRecvQueue.front();//返回第一个元素，但不检查元素是否存在；
			msgRecvQueue.pop_front();//移除第一个元素，但不返回。
			mymutex.unlock();
			return true;
		}
		mymutex.unlock();
		return false;
	}

	//把数据从消息队列中取出的线程
	void outMsgRecvQueue()//线程二
	{
		int command = 0;
		for (int i = 0; i < 100000; ++i)
		{
			bool result = feedback(command);
			if (result == true)
			{
				cout << "outMsgRecvQueue()执行，取出一个元素"  <<command<< endl;
				//Do somthing...
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
	list<int>msgRecvQueue;//容器，串门用于代表玩家给咱们发送过来的命令。
	mutex mymutex;
};


int main()
{
	A myobj;
	thread inMsg(&A::inMsgRecvQuue, &myobj);//第二参数是引用，才能保证线程城里用的是同一个对象。
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
			
			cout << "inMsgRecvQueue()执行，插入元素：" <<i<< endl;
			
		//总结：std::lock();一次锁定多个互斥量；谨慎使用，建议一个一个的锁；
		//mymutex1.lock();//方法1//完全手动lock() & unloc();
		//mymutex2.lock();

		//std::lock_guard<std::mutex>mutex_gard1(mymutex11);//方法2//可以自动unlock()；但是不能解决锁死问题于是发明出了方法4，既能自动解决锁死问题又能自己解决unlock()问题；
		//std::lock_guard<std::mutex>mutex_gard2(mymutex12);
	
		//std::lock(mymutex1, mymutex2);//方法3//遗憾的是不能自动unlock();

			std::lock(mymutex1, mymutex2);//方法4,但是要和方法三一起用，事先写好方法3；既能自动解决锁死问题又能自己解决unlock()问题；
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
				cout << "outMsgRecvQueue()执行，取出一个元素" << commando << endl;
				//Do something...
				//可以考虑进行数据处理
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