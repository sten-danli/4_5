#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;


void myprint()
{
	cout << "�ҵ��߳̿�ʼ�ˡ�" << endl;
	cout<< "�ҵ��߳̽����ˡ�" << endl;
}

class TA
{
public:
	int &m_i;
	TA(int &i):m_i(i)
	{}

	//���������()��������������Ķ��󣬾�������һ������һ����
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
		cout << "m_i��ֵΪ��"<<m_i << endl;

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
	mytobj.join();			//�ȴ�myprint���߳�ִ�н�����������֮���̡߳�
	//mytobj.detach();		//�����̷ֵ߳��������С�
	cout << "main thread end1!" << endl;
	
	return 0;
}











