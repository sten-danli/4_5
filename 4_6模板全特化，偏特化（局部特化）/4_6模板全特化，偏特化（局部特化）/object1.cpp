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

//////////////////////////////////////////////////////////////////////////
//偏特化版本的泛化版本
template<typename T, typename U, typename W>
struct TUW
{
	void functest()
	{
		cout << "泛化版本" << endl;
	}
};
//偏特化的类模板
template<typename U>
struct TUW<int,U,double>//从参数数量上偏特化，我们现在绑定2个类型模板参数，留下一个模板参数。
{
	void functest()
	{
		cout << "偏特化版本执行" << endl;
	}
};
/////////////////////////////////////////////////////////////////////////////


//三。函数模板泛化版本：
template<typename T, typename U>
void tfunc(T& tmp1, U& tmp2)
{
	cout << "函数泛化版本" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;

};

//和篇特化一样，有泛化版本后才可以有全特化版本：
//函数模板q全特化版本：
template<>
void tfunc(int& tmp1, double& tmp2)
{
	cout << "________________begin_________________________";
	cout << "函数全特化版本" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
	cout << "________________end___________________________";
}




int main()
{
	//调用泛化函数

	int i = 5888;
	double j = 58.889;
	tfunc<int, double>(i,j);

	//调用特化函数
	const char* p = "i am python pro!";
	string str = "i am c++ pro ";
	int x = 52888;
	tfunc(p, x);

	TC<char,int> tcchar;
	tcchar.functest();//这是一个泛化版本。

	TC<double, int> tcdi;
	tcdi.functest();//这是一个特化版本。

	TC<double, double> tcdouble;//虽然我们没有给double，double写特化版本类，但是这里调用泛化版本的构造函数。
	tcdouble.functest();//double,double的functest（）特化版本。因为我们特化了double，double类型的functest类型的functest函数，所以这里调用的是特化的functest（）函数。

	TUW<int,char,double> tuw;
	tuw.functest(); //偏特化版本执行
}