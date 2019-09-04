#include<iostream>
using namespace std;



//�ɱ����ģ�壺����ģ�嶨���к���0�������ģ�������
template<typename...Args>
class myclass {};//��ģ��

template<>
class myclass<>//0���������ػ��汾
{
public:
	myclass()
	{
		printf("myclass<>::myclass()0�����ػ��汾ִ����,this = %p\n", this);
	}
};

template<typename T, typename... Other>
class myclass<T,Other...>:myclass<Other...>//ƫ�ػ�
{
public:
	myclass() :m_i(0)
	{
		printf("myclass::myclass()���캯��ִ����,this = %p\n",this);
	}
	myclass(T First, Other...args) :m_i(First), myclass<Other...>(args...)//���ø���Ĺ��캯��myclass<Other...>(args...)
	{
		cout << "m_i=" << m_i << endl;
	}

	T m_i;
};


int main()
{
	myclass<int, string, double>myc(12,"hello",23.8);
}