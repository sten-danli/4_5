#include<iostream>
#include<assert.h>
using namespace std;

size_t my_strlen(const char* str)
{
	assert(str != NULL);
	if (*str == '\0')
		return 0;
	else
		return my_strlen(str + 1) + 1;
}

template<typename...T>
void myfunc(T...args)
{
	cout << sizeof...(args) << endl;
	cout << sizeof...(T) << endl;

}

int main()
{
	myfunc(15, 888, "Hallo i will br Rich!", 58888, "b");

	const char* str = "Hello";
	my_strlen(str);
}
