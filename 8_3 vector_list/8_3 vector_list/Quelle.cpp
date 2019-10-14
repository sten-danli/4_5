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
			cout << "A::A()构造函数执行" << endl;
		}
		A(const A& tmp)
		{
			m_i = tmp.m_i;
			cout << "A:A()拷贝构造函数执行" << endl;
		}
		~A()
		{
			cout<<"析构函数执行"<<endl;
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
			cout <<"下标为"<<i <<"的元素的m_i的值为"<<mydeque[i].m_i << endl;
		}
	}
}

int main()
{
	_nmsp1::func();



}