#include<iostream>
#include<thread>
using namespace std;


#if 0



//void myprint(const int &i, char *pmybuf)//线程函数  //我们希望把他作为一个线程入口//不建议用引用&
void myprint(const int i, const string &pmybuf)//如果不加const在函数内可以更改pmybuf的内容并返回。
{
	//pmybuf = "you are c# pro!"; 
	cout << i << endl;
	cout << pmybuf.c_str() << endl;
	return;
}

int main()
{
	//一：传递临时对象作为线程参数
	int mvar = 1;
	int& myvary = mvar;//引用
	char mybuf[] = "this is a test!";
	thread mythread(myprint,mvar,mybuf);//但是mybuf到底是什么时候转换成string的呢//事实存在，mybuf都被回收了(main函数执行完了)，系统才用mybuf去转换string的可能，这样就会导致错误。
	//thread mythread(myprint, mvar, string(mybuf));//如果我们一定要用detach()方法的话，那我们这里直接将mybuf转换成string对象,这是一个可以保证在线程中用肯定有效的对象。
	mythread.join();//等待子线程完成。
	//mythread.detach();//更不建议用分别进程，因为当mybuf传到*pmybuf形参后，*pmybuf 和 mybuf的地址是同一地址，此时如果主线程先运行完了会释放本地址内存，于是子进程无法访问释放后的地于是出错。
	//坏就坏在detach，它会使我们的主线程很快完成推出并释放内存。
	cout << "i am c++ pro!";//等待子线程完成打印。
	return 0;

}
#endif 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#if 0
//复习3_16类型转换构造函数:主要能力是：它可以将某个其他数据类型转换成该类的类型对象;//其他数据类型(int),本类数据类型(Testint),类型对象(tint)。

//a)只有一个参数，该参数又不是本类的const引用。(const &A),该参数其实就是带转换的数据类型。所以显然待转换的数据类型都不应该是本类类型。
//b)在类型转换构造函数中，我们要指定装欢的方法(在这个函数中要干什么)；
class Testint
{
public:
	int m_i;
	Testint(int x) :m_i(x)
	{
		if (x < 0) { m_i = 0; }
		if (x > 100) { m_i = 100; }
	}
	friend ostream & operator<<(ostream&os, const Testint & t)//operator cout<< 方法。
	{
		return os << t.m_i << endl;
	}
};
int main()
{
	Testint tint = 12;
	cout << tint << endl;
}

#endif 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#if 0
class A
{
public:
	int m_i;
	A(int a) :m_i(a) { cout<<"A::A(int a)构造函数执行" <<this<< endl; }
	A(const A& a) :m_i(a.m_i) { cout << "A::A(const A)拷贝构造函数执行" <<this<< endl; }
	~A()
	{
		cout << "~A执行" <<this<< endl;
	}
};

void myprint(const int i, const A &pmybuf )//子进程
{
	cout << &pmybuf << endl;//对象地址打印
	return;
}


int main()//主进程
{
	int mvar = 1;
	int mysecondpar = 12;
	//thread mytread(myprint, mvar, mysecondpar);//我们希望mysecoundpar转成A类型对象传递给myprint的第二个参数,但是子线程还没运行时主线程就已经运行完并释放。
	thread mytread(myprint, mvar, A(mysecondpar));//这里创建一个临时构造对象 A(mysecondpar)，因次这里在主线程运行完的内存释放之前，已经先创建一个临时对象传到子进程函数中，所以这里thread.detach()运行成功。
									//在创建线程的同时构造临时对象的的方法传递参数时可行的。
	mytread.detach();//如果没有没有在创建线程的同时构造临时对象，主进程运行就后释放内存结束时，子进程将因为没得到主进程信息而没有构造成功。

	cout << "主线程执行" << endl;
	//总结detach()运行成功的方法事实：
	//1. 只要用临时构造的A类对象作为参数传递给线程，那么就一定能够在主线程执行完毕前把线程函数的第二个参数构建出来，从而即使detach()主线程释放也能安全运行。
	//使用detach()时，只要有临时构造对象他就会提前在主线程完成释放内存前构造出来给子线程。
	//a）若传递int这种简单类型参数，建议都是值传递，不要引用。防止节外生枝。//如果不用detach的话那还有这些问题呢。
	//b）如果传递类对象避免隐式类型转换，例如//thread mytread(myprint, mvar, mysecondpar);mysecondpar是个类型，要这样让他显示表达出来他是A类型的A(mysecondpar)
	//全部都在创建线程这一行就构建出临时对象来，然后在函数参数里用引用来接，否侧系统还会构造一次对象，浪费。
	//终极结论：
	//c）建议不使用detach（），只用join（）；这样就不存在局部变量失效导致线程对内存的非法引用问题。
	return 0;
}

 #endif 0



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0



//二：临时对象作为线程参数继续，老师常用测试方法；
//（2.1）线程id概念，：id时个数字，每个线程（不管是主线程还是子线程）实际上都是对应只一个数字，而且每一个线程对应的数字都不同。
//也就是说不同的线程，他的线程id数字必然是不同；
//线程id可以用c++标准的函数来获取。std::this_thread::get_id()来获取；
//(2.2）


class A 
{
	
public:
	mutable int m_i;//mutable 不管在什么情况下我这个m_i这个类都能修改，即便是在一个const的函数中，代表常量的属性中我也能够修改m_i值。
	A(int a) :m_i(a) 
	{ 
		cout << "A::A(int a)构造函数执行    " << this<<" thread_id = " <<std::this_thread::get_id << endl;
		cout << endl;
	}
	A(const A& a) :m_i(a.m_i)
	{ 
		cout << "A::A(const A)拷贝构造函数执行    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	~A()
	{
		cout << "~A执行    " << this << " thread_id = " << std::this_thread::get_id() << endl;
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, const A& t)//operator cout<< 方法。
	{
		return os << t.m_i << endl;
	}
};

void myprint2(const A& pmybuf)
{
	pmybuf.m_i = 199;//因为上面声明了mutable所以这里即使是const依然可以改变。//线程里m_i=199;改变但无法反馈到调用函数,要用std::ref

	cout << "子线程myprint2的参数地址是：    " << &myprint2 << "thread_id = " << std::this_thread::get_id() << endl;
	cout << endl;
	cout <<"子线程修改的m_i的值为: "<< pmybuf.m_i << endl;
	cout << endl;
}



int main()
{
	
	/*cout << "主线程id thread_id是: " << this_thread::get_id() << endl;
	cout << endl;
	
	int myvar = 23;
	thread mythread(myprint2,A(myvar));*/
	
	A myobject(10);//生成一个对象；
	thread mythread(myprint2, std::ref(myobject));
	cout << endl;
	cout<<"主线程m_i: "<<myobject;
	mythread.join();
	//mythread.detach();
	//mythread.detach();//使用时未执行子进程
//
//	主线程												   thread_id = 5892
//	A::A(int a)				构造函数执行	this:010FF644, thread_id = 005B15AF
//	A::A(const A)			拷贝构造函数执行this:014FF170, thread_id = 005B15AF
//	~A执行									this:010FF644, thread_id = 5892


}
#endif // 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//三.传递对象，智能指针作为线程参数
#if 0




void myprintptr(unique_ptr<int>pzn)
{
	cout << "myprintptr子线程 " << endl;
}


int main()
{
	cout << "主线程 " << endl;
	unique_ptr<int>myp(new int(100));
	thread mythread(myprintptr, std::move(myp));
	mythread.join();
}
#endif // 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//四:用成员函数指针做线程函数//可以指定任意一个成员函数作为线程的入口函数

class A
{

public:
	mutable int m_i;//mutable 不管在什么情况下我这个m_i这个类都能修改，即便是在一个const的函数中，代表常量的属性中我也能够修改m_i值。
	A(int a) :m_i(a)
	{
		cout << "A::A(int a)构造函数执行    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	A(const A& a) :m_i(a.m_i)
	{
		cout << "A::A(const A)拷贝构造函数执行    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	~A()
	{
		cout << "~A执行    " << this << " thread_id = " << std::this_thread::get_id() << endl;
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, const A& t)//operator cout<< 方法。
	{
		return os << t.m_i << endl;
	}

public:
	void thread_work(int num)//一个成员函数作为线程执行入口
	{
		cout << "[子线程thread_work执行] " << this << " thread_id = " << std::this_thread::get_id() << endl;
	}
	void operator()()
	{
		cout << "[子线程operator()()执行] " << this << " thread_id = " << std::this_thread::get_id() << endl;
	}
};


int main()
{
	//如何调用A类里面的thread_work函数。
	A obja(10);
	thread mythread(&A::thread_work,obja,15);//&A::thread_work 成员函数的名字前面给出成员函数所在地址，obja 然后是对象名，15线程入口的第一个参数。
	thread mythread1(obja);//[子线程operator()()执行] 
	mythread.join();
	mythread1.join();
}