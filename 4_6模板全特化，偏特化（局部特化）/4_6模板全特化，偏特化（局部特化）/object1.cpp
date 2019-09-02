#include<iostream>
using namespace std;

//一：类模板特化：必须先有泛化版本。只要设计特化，一定存在泛化：
//特化版本代码编译器会优先选择。

//对应1*
//二：单独特化成员函数而不是模板

//1.泛化版本的TU类模板。
template <typename T, typename U>
struct TC
{
	TC()
	{
		cout << "泛化版本构造函数" << endl;
	}
	void functest()
	{
		cout << "这是一个泛化版本" << endl;
	}
};


//2.全特化版本的类模板
//当T和U这两个类型模板都为int类型时，我们希望做一个特化版本
//全特化：就是所有类型模板参数都用具体类型代表，所以这里的template后边的<>里就为空。

template <>
struct TC<double,int>
{
	void functest()
	{
		cout << "这是一个特化版本" << endl;
	}
};

//对应1.
template <>
void TC<double, double>::functest()//单独特化成员函数。
{
	cout << "double,double的functest（）特化版本" << endl;
};




int main()
{
	TC<char,int> tcchar;
	tcchar.functest();//这是一个泛化版本。

	TC<double, int> tcdi;
	tcdi.functest();//这是一个特化版本。

	TC<double, double> tcdouble;//虽然我们没有给double，double写特化版本类，但是这里调用泛化版本的构造函数。
	tcdouble.functest();//double,double的functest（）特化版本。因为我们特化了double，double类型的functest类型的functest函数，所以这里调用的是特化的functest（）函数。


}