//����()��������������Ķ��󣬾�������һ������һ����
#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;


//void operator()()//��ʲô��
//�㣻
//һ�������ó�Ա��������ӷ�����Ҫ��������.
class Math
{
public:
	int i; int j;
public:
	int add(int x, int y)
	{
		return x + y;
	}
	auto operator()(int i, int j)
	{
		return i + j;
	}
};

int main()
{
	Math math1;
	int x=math1.add(1, 2);//һ�������ó�Ա��������ӷ�����Ҫ��������,�ö�����ó�Ա����add
	cout << x << endl;

	 math1(1,2);//��������auto operator()(int i, int j)����ֱ�Ӷ�������һ��ʹ�á�
	
}

//һ��
//��һ��()�ǲ����������� - �����ڶ�����ʹ��()ʱ���õĲ��������ڶ���()���ڲ���������û�С�
//���ʹ������һ�����ӣ�
//background_task task;
//task(); // calls background_task::operator() 

//����
//class A {
//public:
//	void operator()(int x, int y)
	//{
	// Do something 
	//}
//};

//A a;
//a(5, 3); // at this point operator() gets called 
//��һ������ʼ��Ϊ�գ����Ǻ��������ƣ�operator()���ڶ������ſ����в��������ҵ�ʾ������ʾ���������ǲ��أ���������ʾ���У���

//��:
//operator()�Ĳ��ֱ�ʾ����һ�����в����ߣ������ڶ�������ŵ�()ָʾ����û�в����������Ǿ�������������ʾ����һ������ֵ��

//struct add
//{
//	int operator()(int a, int b) const { return a + b; }
//};
//add a;
//int c = a(1, 2); // c initialized to 1+2 

//��;
//��ֻ����������أ���û���κ���C++ 11��֧�ֶ��̡߳����������ֻ��һ����Ȥ���ֵ�����������������е���ڼ򻯣����Գ�ѧ����˵����һ���ܺõľ��鷨�򣩡�
//����class��һ��������Ϊ()���������� �����ϣ������Ҳ��һ����Ϊ����foo��f��TwoParentheses��

//����һ���򵥵����ӣ�
//#include <iostream> 
//class Example
//{
//public:
//	void operator()() { std::cout << "()"; }
//	void foo() { std::cout << "foo"; }
//	void TwoParentheses() { std::cout << "TwoParentheses"; }
//};

//int main()
//{
//	Example e;
//	e.operator()();
//	e.foo();
//	e.TwoParentheses();
//}
//���ں���������������������������main��ƴд������.operator()���֣��Ǻ�û������ģ���Ϊ�����������Ŀ�����õ��ô���򵥡�����Ϊ������ĺ����������ģ�
//int main()
//{
//	Example e;
//	e();
//}
//��������Կ���������e(); ��������ȫһ�����������õĺ�����
//�����Ϊʲôoperator()�Ͼ���һ����������֡���ģ���У�����ʹ��operator()����ͬ���﷨�������

//����һ�£�
//#include <iostream> 
//class Example
//{
//public:
//	void operator()() { std::cout << "Example.operator()\n"; }
//};
//void function() { std::cout << "Function\n"; }

//template <typename T>
//void test(T obj)
//{
//	obj(); // operator() or "real" function 
//}

//int main()
//{
//	Example exanple1;	
//	test(exanple1);		//Example.operator()
//	test(function);		//Function
//}
//�����Ϊʲôoperator()��C++���ͱ�̵�һ����Ҫ���ܣ�������Ҫ��ԭ��

void myprint()
{
	cout << "�ҵ��߳̿�ʼ�ˡ�" << endl;
	cout<< "�ҵ��߳̽����ˡ�" << endl;
}

class TA
{
public:
	int &m_i;
	
	TA(int &i):m_i(i){}

public:
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
	ta.operator()();//���������void operator()()������ӡ�� m_i��ֵΪ��3
	ta();//һ�����������á� //m_i��ֵΪ��3

	thread mytobj(myprint);
	thread mytobj2(ta);  //m_i��ֵΪ��3
	mylamda();	//sum:72
	mytobj.join();			//�ȴ�myprint���߳�ִ�н�����������֮���̡߳�
	mytobj2.join();
	//mytobj.detach();		//�����̷ֵ߳��������С�
	cout << "main thread end1!" << endl;
	
	return 0;
}











