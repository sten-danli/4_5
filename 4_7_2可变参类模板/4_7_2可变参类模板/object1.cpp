#include<iostream>
using namespace std;



//可变参类模板：润许模板定义中含有0到任意个模板参数；
template<typename...Args>
class myclass {};//主模版

template<>
class myclass<>//0个参数的特化版本
{
public:
	myclass()
	{
		printf("myclass<>::myclass()0参数特化版本执行了,this = %p\n", this);
	}
};

template<typename T, typename... Other>
class myclass<T,Other...>:myclass<Other...>//偏特化
{
public:
	myclass() :m_i(0)
	{
		printf("myclass::myclass()构造函数执行了,this = %p\n",this);
	}
	myclass(T First, Other...args) :m_i(First), myclass<Other...>(args...)//调用父类的构造函数myclass<Other...>(args...)
	{
		cout << "m_i=" << m_i << endl;
	}

	T m_i;
};


int main()
{
	myclass<int, string, double>myc(12,"hello",23.8);
}