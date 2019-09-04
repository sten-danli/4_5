//可变参数类模板，用递归组合方式展开参数包
#include<iostream>
using namespace std;

template<typename ...Args> class myclass{};//类模板的声明

template<> class myclass<>//0个参数的特化版本
{
public: 
	myclass()
	{
		printf("myclass<>::myclass() 执行了，this= %p\n", this);
	}
};

template<typename T, typename...Others>
class myclass<T, Others...> :myclass<Others...>
{
public:
	myclass()
	{
		printf("myclass::myclass()构造函数执行,this = %p\n", this);
	}
	myclass(T First, Others...args) :m_i(First),m_o(args...)
	{
		cout << "m_i= " << m_i << endl;
	}

public:
	T m_i;			   
	myclass<Others...> m_o;//组合关系，参数多的类包含参数少的类
};

int main()
{
	myclass<int, string> myc(15968,"fafa");
}