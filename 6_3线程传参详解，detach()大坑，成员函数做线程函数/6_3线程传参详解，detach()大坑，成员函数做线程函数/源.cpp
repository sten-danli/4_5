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
#endif 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#if 0
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

#endif 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





#if 0
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

 #endif 0



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0



//������ʱ������Ϊ�̲߳�����������ʦ���ò��Է�����
//��2.1���߳�id�����idʱ�����֣�ÿ���̣߳����������̻߳������̣߳�ʵ���϶��Ƕ�Ӧֻһ�����֣�����ÿһ���̶߳�Ӧ�����ֶ���ͬ��
//Ҳ����˵��ͬ���̣߳������߳�id���ֱ�Ȼ�ǲ�ͬ��
//�߳�id������c++��׼�ĺ�������ȡ��std::this_thread::get_id()����ȡ��
//(2.2��


class A 
{
	
public:
	mutable int m_i;//mutable ������ʲô����������m_i����඼���޸ģ���������һ��const�ĺ����У�����������������Ҳ�ܹ��޸�m_iֵ��
	A(int a) :m_i(a) 
	{ 
		cout << "A::A(int a)���캯��ִ��    " << this<<" thread_id = " <<std::this_thread::get_id << endl;
		cout << endl;
	}
	A(const A& a) :m_i(a.m_i)
	{ 
		cout << "A::A(const A)�������캯��ִ��    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	~A()
	{
		cout << "~Aִ��    " << this << " thread_id = " << std::this_thread::get_id() << endl;
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, const A& t)//operator cout<< ������
	{
		return os << t.m_i << endl;
	}
};

void myprint2(const A& pmybuf)
{
	pmybuf.m_i = 199;//��Ϊ����������mutable�������Ｔʹ��const��Ȼ���Ըı䡣//�߳���m_i=199;�ı䵫�޷����������ú���,Ҫ��std::ref

	cout << "���߳�myprint2�Ĳ�����ַ�ǣ�    " << &myprint2 << "thread_id = " << std::this_thread::get_id() << endl;
	cout << endl;
	cout <<"���߳��޸ĵ�m_i��ֵΪ: "<< pmybuf.m_i << endl;
	cout << endl;
}



int main()
{
	
	/*cout << "���߳�id thread_id��: " << this_thread::get_id() << endl;
	cout << endl;
	
	int myvar = 23;
	thread mythread(myprint2,A(myvar));*/
	
	A myobject(10);//����һ������
	thread mythread(myprint2, std::ref(myobject));
	cout << endl;
	cout<<"���߳�m_i: "<<myobject;
	mythread.join();
	//mythread.detach();
	//mythread.detach();//ʹ��ʱδִ���ӽ���
//
//	���߳�												   thread_id = 5892
//	A::A(int a)				���캯��ִ��	this:010FF644, thread_id = 005B15AF
//	A::A(const A)			�������캯��ִ��this:014FF170, thread_id = 005B15AF
//	~Aִ��									this:010FF644, thread_id = 5892


}
#endif // 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��.���ݶ�������ָ����Ϊ�̲߳���
#if 0




void myprintptr(unique_ptr<int>pzn)
{
	cout << "myprintptr���߳� " << endl;
}


int main()
{
	cout << "���߳� " << endl;
	unique_ptr<int>myp(new int(100));
	thread mythread(myprintptr, std::move(myp));
	mythread.join();
}
#endif // 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��:�ó�Ա����ָ�����̺߳���//����ָ������һ����Ա������Ϊ�̵߳���ں���

class A
{

public:
	mutable int m_i;//mutable ������ʲô����������m_i����඼���޸ģ���������һ��const�ĺ����У�����������������Ҳ�ܹ��޸�m_iֵ��
	A(int a) :m_i(a)
	{
		cout << "A::A(int a)���캯��ִ��    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	A(const A& a) :m_i(a.m_i)
	{
		cout << "A::A(const A)�������캯��ִ��    " << this << " thread_id = " << std::this_thread::get_id << endl;
		cout << endl;
	}
	~A()
	{
		cout << "~Aִ��    " << this << " thread_id = " << std::this_thread::get_id() << endl;
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, const A& t)//operator cout<< ������
	{
		return os << t.m_i << endl;
	}

public:
	void thread_work(int num)//һ����Ա������Ϊ�߳�ִ�����
	{
		cout << "[���߳�thread_workִ��] " << this << " thread_id = " << std::this_thread::get_id() << endl;
	}
	void operator()()
	{
		cout << "[���߳�operator()()ִ��] " << this << " thread_id = " << std::this_thread::get_id() << endl;
	}
};


int main()
{
	//��ε���A�������thread_work������
	A obja(10);
	thread mythread(&A::thread_work,obja,15);//&A::thread_work ��Ա����������ǰ�������Ա�������ڵ�ַ��obja Ȼ���Ƕ�������15�߳���ڵĵ�һ��������
	thread mythread1(obja);//[���߳�operator()()ִ��] 
	mythread.join();
	mythread1.join();
}