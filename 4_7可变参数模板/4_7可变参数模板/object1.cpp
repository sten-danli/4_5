#include<iostream>
#include<assert.h>
using namespace std;

//一：可变惨函数模板
//可变参数模板的参数包打开方法
void myfunc()
{
	cout << "开包结束" << endl;
}
template<typename T, typename...U>
void myfunc(const T& first, const U&...args)
{
	cout << "args的参数值为: " <<first<< endl;
	myfunc(args...);
}

//递归str_lende的方法：
size_t my_strlen(const char* str)
{
	assert(str!=NULL);
	if (*str == '\0')
		return 0;
	else
		return my_strlen(str + 1)+1;
}

//可变惨函数模板练习

void myfuncprintout()
{
	cout << "以上为args全部内容。" << endl;
}
template<typename T>
void myfuncprintout(const T& first)
{
	cout << first << endl;
	cout << "以上为args全部内容。" << endl;
}

template<typename T, typename ...U>
void myfuncprintout(const T& first, const U& ...args)
{
	cout << "args内的所有内容是： " << first <<"," <<endl;
	myfuncprintout(args...);
}

int main()
{
	double x = 2.71828;
	string mr = "i will be c++ profi!";
	myfuncprintout(x, mr);

	//递归str_lende的方法：
	const char* str = "i will by professional hacker!";
	cout << "str的长度是： "<<my_strlen(str) << endl;

	//可变参数模板的参数包打开方法:
	myfunc("hello",12,34);
}