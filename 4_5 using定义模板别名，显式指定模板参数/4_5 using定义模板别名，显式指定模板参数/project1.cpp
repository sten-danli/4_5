//用using 定义类型或类型模板
#include<iostream>
#include<map>
using namespace std;

//*对应2
//需求：希望定义一个类型，前边这部分固定不变，是std::map<std::string, 类型自己制定>
//在c++98时代
template<typename T>
class map_s//定义了一个结构/类，只是结构的成员都是public
{
public:
	typedef std::map<string,T >type;//定义了一个类型,以string为建，以T类型为值 给map这个容器，在98时代
	//我们不得不写一个map_s的这样的类来达到目的。
};
///////////////////////////////////////////////

//*对应3
//在c++2011时代
template <typename T>
using str_map_t = std::map<std::string, int>;//str_map_t是类型的别名。
//using用来给一个【类型】起名字（别名）用的.

//using在用于定义类型和类型模板的是后，是包括了typedef的所有功能,下面是分别用using和typedef的区别：
typedef unsigned int uint_t;
using uint_t = unsigned int;

typedef std::map<std::string, int> map_t;
using map_u =std::map<std::string, int>;

typedef int (*pfuncType)(int, int);	//用typedef定义一个函数指针；
using pfun = int (*)(int, int);		//用using定义一个函数指针；

//*对应4
//一个函数指针举例说明
template<typename T>
using myfunc_M=T(*)(T,T);//定义类型模板，是个函数指针模板。//注意myfunc_M现在是以哦个类型哦。

int Realfunc(int i, int j)
{
	return 1;
}

//二：显示指定模板参数
//*对应5
template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}

int main()
{

	//对应4：如何调用函数指针。
	myfunc_M<int> mypfunc; //myfunc_M<int>是一个函数指针类型。
						   //myPfunc是一个函数指针.

	mypfunc = Realfunc;//把函数地址付给函数指针变量。
	cout << Realfunc(199, 288) << endl;//1
	

	//对应3
	str_map_t<int> mymap1;
	mymap1.insert({ "first",2 });

	//对应2
	map_s<string>::type mymapstruct;
	mymapstruct.insert({ "first","ha" });


//一：using定义模板别名
	//用typedef定义一个类型别名：一般用来定义类型别名。
	typedef unsigned int uint_t;//相当于给unsigned int类型起了个别名unint_:t
	//std::map<std::string,int>

	typedef std::map <string, int>map_s_i;
	map_s_i mymap;
	mymap.insert({ "first", 1 });
	mymap.insert({ "secound", 2 });

	typedef map<string,string>map_s_s;
	map_s_s mymap2;
	mymap2.insert({ "first","firstone"});
	
	//总结：
	//using中使用这种模板，既不是类模板，也不是函数模板，我们可以看成是一种新的模板类型：类型模板（模板别名）；
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//二：显示指定模板参数
	//对应5：显式指定模板参数的调用
	auto result = sum<double,double,double>(2000000000, 20000000000);//这里必须显示地给出类型，因为二十个亿不能
	//推断出来，只能用double的显示给出。
	cout << result << endl;

	
}

