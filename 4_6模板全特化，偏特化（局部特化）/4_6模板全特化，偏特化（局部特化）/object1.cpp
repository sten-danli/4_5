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




int main()
{
	TC<char,int> tcchar;
	tcchar.functest();//����һ�������汾��

	TC<double, int> tcdi;
	tcdi.functest();//����һ���ػ��汾��

	TC<double, double> tcdouble;//��Ȼ����û�и�double��doubleд�ػ��汾�࣬����������÷����汾�Ĺ��캯����
	tcdouble.functest();//double,double��functest�����ػ��汾����Ϊ�����ػ���double��double���͵�functest���͵�functest����������������õ����ػ���functest����������


}