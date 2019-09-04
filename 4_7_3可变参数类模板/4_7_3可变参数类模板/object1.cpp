//�ɱ������ģ�壬�õݹ���Ϸ�ʽչ��������
#include<iostream>
using namespace std;

template<typename ...Args> class myclass{};//��ģ�������

template<> class myclass<>//0���������ػ��汾
{
public: 
	myclass()
	{
		printf("myclass<>::myclass() ִ���ˣ�this= %p\n", this);
	}
};

template<typename T, typename...Others>
class myclass<T, Others...> :myclass<Others...>
{
public:
	myclass()
	{
		printf("myclass::myclass()���캯��ִ��,this = %p\n", this);
	}
	myclass(T First, Others...args) :m_i(First),m_o(args...)
	{
		cout << "m_i= " << m_i << endl;
	}

public:
	T m_i;			   
	myclass<Others...> m_o;//��Ϲ�ϵ�������������������ٵ���
};

int main()
{
	myclass<int, string> myc(15968,"fafa");
}