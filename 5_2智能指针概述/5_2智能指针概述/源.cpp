#include<iostream>
using namespace std;


//int* pint = new int(100);
//shared_ptr<int>pint2(new int (100));//pi��һ��ָ��ֵΪ100��int�������ݡ�
//shared_ptr<string>pstring(new string(5, 'a'));
//
//shared_ptr<int> makes(int value1)
//{
//	return shared_ptr<int>(new int(value1));	 
//}

//mak_shared��������׼��������ĺ���ģ�塣��ȫ��Ч�ķ����ʹ��shared_ptr;
//���ܹ��ڶ�̬�ڴ棨�ѣ�stack�з��䲢��ʼ��һ������Ȼ�󷵻�ָ��˶����share_ptr;
shared_ptr<int> pp2 = make_shared<int>(100);//���shared_ptrָ��һ��ֵΪ100�������ڴ棬�е�����int*pi=new int(100);
																			//�������ܹ������ڴ滹�ܷ���һ������ָ�����͸�p2��
shared_ptr<string>pp3=make_shared<string>(5, 'a');//5���ַ�a���ɵ��ַ�����
			//������string mystr��5,'a'��;



int main()
{
	shared_ptr<int> pp4 = make_shared<int>();//pp4ָ��һ��int��int���ֵ��ʼ����ֵ��0��
	pp4 = make_shared<int>(5889);//pp4ָ��һ����int��int���汣�����5889��pp4�����ͷŸղ�ָ���ֵΪ0���ڴ棬Ȼ��ָ��������ڴ��5889���ֵ��

	auto pp5 = make_shared<string>(8, 'a');//���auto pp5�ȼ���shared_ptr<string>pp3 = make_shared<string>(5, 'a'); �����Զ��ƶϳ����͡�
	cout << pp5.use_count() << endl;;//��ʾָ��֮���������//1
	auto pp6(pp5);//��һ�µ�ָ��ָ��.
	cout << pp6.use_count()<<endl;//2
	auto pp7 = pp5;
	cout << pp7.use_count() << endl;//3


	//auto  p = makes(99);//99
	//shared_ptr<int> ps = makes(99);//99
	//shared_ptr<string>bp = pstring;
	//cout << *pstring << endl;
	//cout << *p << endl;
	//cout << *bp << endl;
	//shared_ptr<int> p2 = p;
	//cout << *pint2 << endl;//999
	//cout<<p.use_count();//2
}