#include<iostream>
#include <deque>
using namespace std;


namespace _nmsp1
{
	
	class A
	{
	public:
		int m_i;
		A(int tmp) :m_i(tmp)
		{
			cout << "A::A()���캯��ִ��" << endl;
		}
		A(const A& tmp)
		{
			m_i = tmp.m_i;
			cout << "A:A()�������캯��ִ��" << endl;
		}
		~A()
		{
			cout<<"��������ִ��"<<endl;
		}
	};


	void func()
	{
		deque<A> mydeque;
		for (int i = 0; i < 5; ++i)
		{
			cout << "----------------begin--------------" << endl;
			mydeque.push_front(A(i));
			cout << "----------------end--------------" << endl;
		}
		for (int i = 0; i < 5; ++i)
		{
			cout << "----------------begin2--------------" << endl;
			mydeque.push_back(A(i));
			cout << "----------------end2--------------" << endl;
		}
		for (int i = 0; i < mydeque.size(); ++i)
		{
			cout <<"�±�Ϊ"<<i <<"��Ԫ�ص�m_i��ֵΪ"<<mydeque[i].m_i << endl;
		}
	}
}

int main()
{
	_nmsp1::func();



}