#include<iostream>
#include<thread>
using namespace std;



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