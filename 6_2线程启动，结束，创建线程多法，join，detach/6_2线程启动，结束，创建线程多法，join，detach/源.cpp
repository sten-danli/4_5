#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;


void myprint()
{
	cout << "我的线程开始了。" << endl;
	cout<< "我的线程结束了。" << endl;
}

class TA
{
public:
	int &m_i;
	TA(int &i):m_i(i)
	{}

	//你可以重载()操作符来调用你的对象，就像它是一个函数一样：
	//	class A {
	//	public:
	//		void operator()(int x, int y) {
	//			// Do something
	//		}
	//};
	//A x;
	//x(5, 3); // at this point operator () gets called
	void operator()()
	{
		cout << "m_i的值为；"<<m_i << endl;

	}
};
auto mylamda = []
{
	int x = 8;
	int y = 9;
	auto sum = x * y;
	cout << "sum:" << sum << endl;
};
int main()
{
	int x = 3;
	TA ta(x);

	thread mytobj(myprint);
	mylamda();
	mytobj.join();			//等待myprint子线程执行结束后再运行之后线程。
	//mytobj.detach();		//各自线程分道扬镳运行。
	cout << "main thread end1!" << endl;
	
	return 0;
}











