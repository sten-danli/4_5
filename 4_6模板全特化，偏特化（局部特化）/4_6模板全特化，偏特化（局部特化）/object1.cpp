#include<iostream>
using namespace std;

//һ����ģ���ػ����������з����汾��ֻҪ����ػ���һ�����ڷ�����
//�ػ��汾���������������ѡ��

//��Ӧ1*
//���������ػ���Ա����������ģ��

//1.�����汾��TU��ģ�塣
template <typename T, typename U>
struct TC
{
	TC()
	{
		cout << "�����汾���캯��" << endl;
	}
	void functest()
	{
		cout << "����һ�������汾" << endl;
	}
};


//2.ȫ�ػ��汾����ģ��
//��T��U����������ģ�嶼Ϊint����ʱ������ϣ����һ���ػ��汾
//ȫ�ػ���������������ģ��������þ������ʹ������������template��ߵ�<>���Ϊ�ա�

template <>
struct TC<double,int>
{
	void functest()
	{
		cout << "����һ���ػ��汾" << endl;
	}
};

//��Ӧ1.
template <>
void TC<double, double>::functest()//�����ػ���Ա������
{
	cout << "double,double��functest�����ػ��汾" << endl;
};

//////////////////////////////////////////////////////////////////////////
//ƫ�ػ��汾�ķ����汾
template<typename T, typename U, typename W>
struct TUW
{
	void functest()
	{
		cout << "�����汾" << endl;
	}
};
//ƫ�ػ�����ģ��
template<typename U>
struct TUW<int,U,double>//�Ӳ���������ƫ�ػ����������ڰ�2������ģ�����������һ��ģ�������
{
	void functest()
	{
		cout << "ƫ�ػ��汾ִ��" << endl;
	}
};
/////////////////////////////////////////////////////////////////////////////


//��������ģ�巺���汾��
template<typename T, typename U>
void tfunc(T& tmp1, U& tmp2)
{
	cout << "���������汾" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;

};

//��ƪ�ػ�һ�����з����汾��ſ�����ȫ�ػ��汾��
//����ģ��qȫ�ػ��汾��
template<>
void tfunc(int& tmp1, double& tmp2)
{
	cout << "________________begin_________________________";
	cout << "����ȫ�ػ��汾" << endl;
	cout << tmp1 << endl;
	cout << tmp2 << endl;
	cout << "________________end___________________________";
}




int main()
{
	//���÷�������

	int i = 5888;
	double j = 58.889;
	tfunc<int, double>(i,j);

	//�����ػ�����
	const char* p = "i am python pro!";
	string str = "i am c++ pro ";
	int x = 52888;
	tfunc(p, x);

	TC<char,int> tcchar;
	tcchar.functest();//����һ�������汾��

	TC<double, int> tcdi;
	tcdi.functest();//����һ���ػ��汾��

	TC<double, double> tcdouble;//��Ȼ����û�и�double��doubleд�ػ��汾�࣬����������÷����汾�Ĺ��캯����
	tcdouble.functest();//double,double��functest�����ػ��汾����Ϊ�����ػ���double��double���͵�functest���͵�functest����������������õ����ػ���functest����������

	TUW<int,char,double> tuw;
	tuw.functest(); //ƫ�ػ��汾ִ��
}