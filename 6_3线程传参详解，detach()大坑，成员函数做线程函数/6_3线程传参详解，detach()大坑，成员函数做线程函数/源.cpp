#include<iostream>
#include<thread>
using namespace std;


#if 0



//void myprint(const int &i, char *pmybuf)//�̺߳���  //����ϣ��������Ϊһ���߳����//������������&
void myprint(const int i, const string &pmybuf)//�������const�ں����ڿ��Ը���pmybuf�����ݲ����ء�
{
	//pmybuf = "you are c# pro!"; 
	cout << i << endl;
	cout << pmybuf.c_str() << endl;
	return;
}

int main()
{
	//һ��������ʱ������Ϊ�̲߳���
	int mvar = 1;
	int& myvary = mvar;//����
	char mybuf[] = "this is a test!";
	thread mythread(myprint,mvar,mybuf);//����mybuf������ʲôʱ��ת����string����//��ʵ���ڣ�mybuf����������(main����ִ������)��ϵͳ����mybufȥת��string�Ŀ��ܣ������ͻᵼ�´���
	//thread mythread(myprint, mvar, string(mybuf));//�������һ��Ҫ��detach()�����Ļ�������������ֱ�ӽ�mybufת����string����,����һ�����Ա�֤���߳����ÿ϶���Ч�Ķ���
	mythread.join();//�ȴ����߳���ɡ�
	//mythread.detach();//���������÷ֱ���̣���Ϊ��mybuf����*pmybuf�βκ�*pmybuf �� mybuf�ĵ�ַ��ͬһ��ַ����ʱ������߳����������˻��ͷű���ַ�ڴ棬�����ӽ����޷������ͷź�ĵ����ǳ���
	//���ͻ���detach������ʹ���ǵ����̺߳ܿ�����Ƴ����ͷ��ڴ档
	cout << "i am c++ pro!";//�ȴ����߳���ɴ�ӡ��
	return 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ϰ3_16����ת�����캯��:��Ҫ�����ǣ������Խ�ĳ��������������ת���ɸ�������Ͷ���;//������������(int),������������(Testint),���Ͷ���(tint)��

//a)ֻ��һ���������ò����ֲ��Ǳ����const���á�(const &A),�ò�����ʵ���Ǵ�ת�����������͡�������Ȼ��ת�����������Ͷ���Ӧ���Ǳ������͡�
//b)������ת�����캯���У�����Ҫָ��װ���ķ���(�����������Ҫ��ʲô)��
class Testint
{
public:
	int m_i;
	Testint(int x) :m_i(x)
	{
		if (x < 0) { m_i = 0; }
		if (x > 100) { m_i = 100; }
	}
	friend ostream & operator<<(ostream&os, const Testint & t)//operator cout<< ������
	{
		return os << t.m_i << endl;
	}
};
int main()
{
	Testint tint = 12;
	cout << tint << endl;
}

#endif 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////







class A
{
public:
	int m_i;
	A(int a) :m_i(a) { cout<<"A::A(int a)���캯��ִ��" <<this<< endl; }
	A(const A& a) :m_i(a.m_i) { cout << "A::A(const A)�������캯��ִ��" <<this<< endl; }
	~A()
	{
		cout << "~Aִ��" <<this<< endl;
	}
};

void myprint(const int i, const A &pmybuf )//�ӽ���
{
	cout << &pmybuf << endl;//�����ַ��ӡ
	return;
}


int main()//������
{
	int mvar = 1;
	int mysecondpar = 12;
	//thread mytread(myprint, mvar, mysecondpar);//����ϣ��mysecoundparת��A���Ͷ��󴫵ݸ�myprint�ĵڶ�������,�������̻߳�û����ʱ���߳̾��Ѿ������겢�ͷš�
	thread mytread(myprint, mvar, A(mysecondpar));//���ﴴ��һ����ʱ������� A(mysecondpar)��������������߳���������ڴ��ͷ�֮ǰ���Ѿ��ȴ���һ����ʱ���󴫵��ӽ��̺����У���������thread.detach()���гɹ���
									//�ڴ����̵߳�ͬʱ������ʱ����ĵķ������ݲ���ʱ���еġ�
	mytread.detach();//���û��û���ڴ����̵߳�ͬʱ������ʱ�������������оͺ��ͷ��ڴ����ʱ���ӽ��̽���Ϊû�õ���������Ϣ��û�й���ɹ���

	cout << "���߳�ִ��" << endl;
	//�ܽ�detach()���гɹ��ķ�����ʵ��
	//1. ֻҪ����ʱ�����A�������Ϊ�������ݸ��̣߳���ô��һ���ܹ������߳�ִ�����ǰ���̺߳����ĵڶ������������������Ӷ���ʹdetach()���߳��ͷ�Ҳ�ܰ�ȫ���С�
	//ʹ��detach()ʱ��ֻҪ����ʱ����������ͻ���ǰ�����߳�����ͷ��ڴ�ǰ������������̡߳�
	//a��������int���ּ����Ͳ��������鶼��ֵ���ݣ���Ҫ���á���ֹ������֦��//�������detach�Ļ��ǻ�����Щ�����ء�
	//b�������������������ʽ����ת��������//thread mytread(myprint, mvar, mysecondpar);mysecondpar�Ǹ����ͣ�Ҫ����������ʾ����������A���͵�A(mysecondpar)
	//ȫ�����ڴ����߳���һ�о͹�������ʱ��������Ȼ���ں������������������ӣ����ϵͳ���ṹ��һ�ζ����˷ѡ�
	//�ռ����ۣ�
	//c�����鲻ʹ��detach������ֻ��join�����������Ͳ����ھֲ�����ʧЧ�����̶߳��ڴ�ķǷ��������⡣
	return 0;
}