#include<iostream>
#include<assert.h>
using namespace std;

//һ���ɱ�Һ���ģ��
//�ɱ����ģ��Ĳ������򿪷���
void myfunc()
{
	cout << "��������" << endl;
}
template<typename T, typename...U>
void myfunc(const T& first, const U&...args)
{
	cout << "args�Ĳ���ֵΪ: " <<first<< endl;
	myfunc(args...);
}

//�ݹ�str_lende�ķ�����
size_t my_strlen(const char* str)
{
	assert(str!=NULL);
	if (*str == '\0')
		return 0;
	else
		return my_strlen(str + 1)+1;
}

//�ɱ�Һ���ģ����ϰ

void myfuncprintout()
{
	cout << "����Ϊargsȫ�����ݡ�" << endl;
}
template<typename T>
void myfuncprintout(const T& first)
{
	cout << first << endl;
	cout << "����Ϊargsȫ�����ݡ�" << endl;
}

template<typename T, typename ...U>
void myfuncprintout(const T& first, const U& ...args)
{
	cout << "args�ڵ����������ǣ� " << first <<"," <<endl;
	myfuncprintout(args...);
}

int main()
{
	double x = 2.71828;
	string mr = "i will be c++ profi!";
	myfuncprintout(x, mr);

	//�ݹ�str_lende�ķ�����
	const char* str = "i will by professional hacker!";
	cout << "str�ĳ����ǣ� "<<my_strlen(str) << endl;

	//�ɱ����ģ��Ĳ������򿪷���:
	myfunc("hello",12,34);
}