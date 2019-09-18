//重载()操作符来调用你的对象，就像它是一个函数一样：
#include<iostream>
#include<thread>
#include<Windows.h>
using namespace std;


//void operator()()//是什么：
//零；
//一般对象调用成员函数例如加法函数要这样调用.
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
	int x=math1.add(1, 2);//一般对象调用成员函数例如加法函数要这样调用,用对象调用成员函数add
	cout << x << endl;

	 math1(1,2);//但是用了auto operator()(int i, int j)可以直接对象像函数一样使用。
	
}

//一：
//第一个()是操作符的名称 - 它是在对象上使用()时调用的操作符。第二个()用于参数，其中没有。
//如何使用它的一个例子：
//background_task task;
//task(); // calls background_task::operator() 

//二：
//class A {
//public:
//	void operator()(int x, int y)
	//{
	// Do something 
	//}
//};

//A a;
//a(5, 3); // at this point operator() gets called 
//第一个括号始终为空：这是函数的名称：operator()，第二个括号可能有参数（如我的示例中所示），但他们不必（如在您的示例中）。

//三:
//operator()的部分表示它是一个呼叫操作者，所述第二组空括号的()指示操作没有参数。下面是具有两个参数的示例和一个返回值：

//struct add
//{
//	int operator()(int a, int b) const { return a + b; }
//};
//add a;
//int c = a(1, 2); // c initialized to 1+2 

//四;
//这只是运算符重载，并没有任何与C++ 11或支持多线程。重载运算符只是一个有趣名字的正常函数（这可能有点过于简化，但对初学者来说这是一个很好的经验法则）。
//您的class有一个函数名为()。就这样。 技术上，你可能也有一个名为功能foo或f或TwoParentheses。

//考虑一个简单的例子：
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
//现在呼吁在这个例子中重载运算符就像main，拼写出整个.operator()部分，是很没有意义的，因为重载运算符的目的是让调用代码简单。你会改为调用你的函数是这样的：
//int main()
//{
//	Example e;
//	e();
//}
//正如你可以看到，现在e(); 看起来完全一样，如果你调用的函数。
//这就是为什么operator()毕竟是一个特殊的名字。在模板中，可以使用operator()和相同的语法处理对象。

//考虑一下：
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
//这就是为什么operator()在C++泛型编程的一个重要功能，往往需要的原因。

void myprint()
{
	cout << "我的线程开始了。" << endl;
	cout<< "我的线程结束了。" << endl;
}

class TA
{
public:
	int &m_i;
	
	TA(int &i):m_i(i){}

public:
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
	ta.operator()();//这里掉用了void operator()()，并打印出 m_i的值为；3
	ta();//一般是这样调用。 //m_i的值为；3

	thread mytobj(myprint);
	thread mytobj2(ta);  //m_i的值为；3
	mylamda();	//sum:72
	mytobj.join();			//等待myprint子线程执行结束后再运行之后线程。
	mytobj2.join();
	//mytobj.detach();		//各自线程分道扬镳运行。
	cout << "main thread end1!" << endl;
	
	return 0;
}











