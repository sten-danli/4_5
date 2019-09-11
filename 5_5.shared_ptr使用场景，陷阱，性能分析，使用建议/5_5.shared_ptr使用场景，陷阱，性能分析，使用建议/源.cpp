#include<iostream>
using namespace std;


shared_ptr<int>createO(int value)
{
	//return shared_ptr<int>(new int(value));
	return make_shared<int>(value);//返回一个shared_ptr。
}

shared_ptr<int> myfunc(int value)
{
	
	 shared_ptr<int>ptemp = createO(10);//离开作用域后ptemp会被释放，他所指向的内存也会被自动释放。
	 return ptemp;
}

//auto myfunc(int value)//上面代码我试着写成了这样。
//{
//
//	auto ptemp = createO(10);//离开作用域后ptemp会被释放，他所指向的内存也会被自动释放。
//	return ptemp;
//}
//////////////////////////////////////////////////////////////////////////
class TC:public enable_shared_from_this<TC>
{
public:
	shared_ptr<TC> getself()//获取我自己
	{
		cout << "TC自己的this地址是： "<<this << endl;//用裸指针初始化了多个shared ptr的感觉；导致ptc1和ptc2失去关联，两个指针的计数都为1。
		//return shared_ptr<TC>(this);//this代表对象自己
		return shared_from_this();//这个就是enable shared form this类中的方法，要通过此方法返回智能指针。

	}
};
//////////////////////////////////////////////////////////////////////////
int main()
{
	auto ptr = myfunc(12);
	cout <<*ptr<< endl;

//(2.2)慎用get（）返回的指针。
	//返回智能指针指向的对象所对应的那裸指针（有些函数接口可能智能使用裸指针）
	//get返回来的裸指针不能delete否则回异常.
	shared_ptr<int>myp(new int(100));
	int* p = myp.get();//get在这里返回了myp指向的地址。
	auto ps =myp.get();//get在这里返回了myp指向的地址。
	cout <<myp<<","<< p <<","<<ps<< endl;//打印出三个同样的地址。
	//delete ps;//不可以删除，会导致异常，因为myp已经是交给智能指针管理，所以你不能delete。

	//不能将其他智能指针帮到get返回的指针上，举例如下：
	shared_ptr<int>myp2(new int(100));
	int* p2 = myp2.get();//这种指针千万不能随意释放。
	{
		//可行方法：
		shared_ptr<int>myp3(myp2);//用智能指针去接住myp2就可行。
		//不可行方法：
		//shared_ptr<int>myp2(p2);//现在myp2和myp3的引用指数都为1， 但一旦跳出了这个程序快的这个范围,
		
	}
	//导致myp指向的内存被释放了。
	*myp2 = 65;//该内存已经被释放，这样赋值会导致不可预料的后果；
	//结论：永远不要用get得到的指针来初始化另外一个智能指针赋值。
	

	//(2.3)不要把类对象指针（this）作为shared ptr返回，改用enable_shared_from_this
	shared_ptr<TC>ptc1(new TC);
	//shared_ptr<TC>ptc2 = ptc1;//这是两个强引用；
	shared_ptr<TC>ptc2 = ptc1->getself();//不可用，ptc1和ptc2失去关联，两个指针的计数都为1。
	//此时要用c++标准库里边的类模板：enable_shared_from_this就可以使ptc1和ptc2贯通，两个计数器为2.
	//现在在外面创建TC对象的智能指针以及通过TC对象返回的this智能指针都是安全的；
	//enable_shared_from_this中有一个弱指针，这个弱指针能够监视this，
	//在我们调用shared from this()这个方法时，这个方法内部实际上调用了这个weak ptr的lock（）方法；
	//大家都知道lock（）方法会让shared ptr指针计数+1,同时返回这个shared ptr，这个就是工作原理；







	return 0;
}