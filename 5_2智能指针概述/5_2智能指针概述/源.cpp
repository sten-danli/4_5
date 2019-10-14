#include<iostream>
using namespace std;

//�����ʼ����shared_ptr��new��ϣ�

shared_ptr<int>p1;//ָ��int������ָ�룬��p1����Ŀǰֻ��Ϊ�գ���ָ�룬nullptr��
shared_ptr<int>p2(new int);//��ʼ��һ��p1ָ��
int* p3 = (new int(100));//pintָ��һ��ֵΪ100��int����
shared_ptr<int>p4(new int (100));//p4��һ��ָ��ֵΪ100��int�������ݡ�
shared_ptr<string>pstring(new string(5, 'a'));

shared_ptr<string> makes(string value1)//
{
	return shared_ptr<string>(new string(value1));	 //����һ������ָ��//����ʵ����int*����shared_ptr<int>
}

void swap(shared_ptr<int>&a, shared_ptr<int>&b)//������ָ�뵱��ʵ����������ת�ݣ�
{
	shared_ptr<int> temp;
	temp = a;
	a = b;
	b = temp;
}

shared_ptr<int>myfunc(shared_ptr<int>& temp)//��Ϊ�����ķ���ֵ
{
	return temp;
}


int main()
{
	//mak_shared��������׼��������ĺ���ģ�塣��ȫ��Ч�ķ����ʹ��shared_ptr;
	//���ܹ��ڶ�̬�ڴ棨�ѣ�stack�з��䲢��ʼ��һ������Ȼ�󷵻�ָ��˶����share_ptr;

	shared_ptr<int> pp2 = make_shared<int>(100);//���shared_ptrָ��һ��ֵΪ100�������ڴ棬�е�����int*pi=new int(100);
																				//�������ܹ������ڴ滹�ܷ���һ������ָ�����͸�p2��
	shared_ptr<string>pp3 = make_shared<string>(5, 'a');//5���ַ�a���ɵ��ַ�����
				//������string mystr��5,'a'��;
	shared_ptr<int> pp4 = make_shared<int>();//pp4ָ��һ��int��int���ֵ��ʼ����ֵ��0��
	pp4 = make_shared<int>(5889);//pp4ָ��һ����int��int���汣�����5889��pp4�����ͷŸղ�ָ���ֵΪ0���ڴ棬Ȼ��ָ��������ڴ��5889���ֵ��

	auto pp5 = make_shared<string>(8, 'a');//���auto pp5�ȼ���shared_ptr<string>pp3 = make_shared<string>(5, 'a'); �����Զ��ƶϳ����͡�
	cout << pp5.use_count() << endl;;//��ʾָ��֮���������//1
	auto pp6(pp5);//��һ�µ�ָ��ָ��.
	cout << pp6.use_count()<<endl;//2
	auto pp7 = pp5;
	cout << pp7.use_count() << endl;//3

	cout << "Bitter string eingeben:"<<endl;
	string valueeingeben;
	cin >> valueeingeben;
	auto  p = makes(valueeingeben);
	cout << "Sie Haben: " << *p <<" Eingegeben."<< endl;//makes = hello


	auto a = make_shared<int>(99);
	auto b = make_shared<int>(100);
	//int a = 99;
	//int b = 100;

	//������ָ�뵱��ʵ����������ת��
	swap(a, b);
	cout << "a = " << *a << " b = " << *b << endl;

	//��Ϊ�����ķ���ֵ��
	auto pfunc = myfunc(pp4);
	cout << "��Ϊ��������ֵΪ�� "<<*pfunc << endl;
	cout<<"һ���ж���ָ��ָ��pp4: "<<pp4.use_count()<<endl;

	//ָ�����������
	auto ppint1 = make_shared<int>(100);
	auto ppint2 = make_shared<int>(100);
	ppint1 = ppint2;
	cout << "ppint1 ָ������Ϊ: " << ppint1.use_count() << " ppint2 ָ������Ϊ: " << ppint2.use_count() << endl;
	//��ppint1��ֵ����ppint1ָ��ppint2ָ��Ķ��󣬸ö������ü������2����ԭ��pp1��ָ��Ķ������ü������1��Ϊ0��
	//�Ӷ����±��ͷš�


	//shared_ptr<int> ps = makes(99);//99
	//shared_ptr<string>bp = pstring;
	//cout << *pstring << endl;
	
	//cout << *bp << endl;
	//shared_ptr<int> p2 = p;
	//cout << *pint2 << endl;//999
	//cout<<p.use_count();//2
}