#include<iostream>
using namespace std;


shared_ptr<int>createO(int value)
{
	//return shared_ptr<int>(new int(value));
	return make_shared<int>(value);//����һ��shared_ptr��
}

shared_ptr<int> myfunc(int value)
{
	
	 shared_ptr<int>ptemp = createO(10);//�뿪�������ptemp�ᱻ�ͷţ�����ָ����ڴ�Ҳ�ᱻ�Զ��ͷš�
	 return ptemp;
}

//auto myfunc(int value)//�������������д����������
//{
//
//	auto ptemp = createO(10);//�뿪�������ptemp�ᱻ�ͷţ�����ָ����ڴ�Ҳ�ᱻ�Զ��ͷš�
//	return ptemp;
//}
//////////////////////////////////////////////////////////////////////////
class TC:public enable_shared_from_this<TC>
{
public:
	shared_ptr<TC> getself()//��ȡ���Լ�
	{
		cout << "TC�Լ���this��ַ�ǣ� "<<this << endl;//����ָ���ʼ���˶��shared ptr�ĸо�������ptc1��ptc2ʧȥ����������ָ��ļ�����Ϊ1��
		//return shared_ptr<TC>(this);//this��������Լ�
		return shared_from_this();//�������enable shared form this���еķ�����Ҫͨ���˷�����������ָ�롣

	}
};
//////////////////////////////////////////////////////////////////////////
int main()
{
	auto ptr = myfunc(12);
	cout <<*ptr<< endl;

//(2.2)����get�������ص�ָ�롣
	//��������ָ��ָ��Ķ�������Ӧ������ָ�루��Щ�����ӿڿ�������ʹ����ָ�룩
	//get����������ָ�벻��delete������쳣.
	shared_ptr<int>myp(new int(100));
	int* p = myp.get();//get�����ﷵ����mypָ��ĵ�ַ��
	auto ps =myp.get();//get�����ﷵ����mypָ��ĵ�ַ��
	cout <<myp<<","<< p <<","<<ps<< endl;//��ӡ������ͬ���ĵ�ַ��
	//delete ps;//������ɾ�����ᵼ���쳣����Ϊmyp�Ѿ��ǽ�������ָ����������㲻��delete��

	//���ܽ���������ָ��ﵽget���ص�ָ���ϣ��������£�
	shared_ptr<int>myp2(new int(100));
	int* p2 = myp2.get();//����ָ��ǧ���������ͷš�
	{
		//���з�����
		shared_ptr<int>myp3(myp2);//������ָ��ȥ��סmyp2�Ϳ��С�
		//�����з�����
		//shared_ptr<int>myp2(p2);//����myp2��myp3������ָ����Ϊ1�� ��һ����������������������Χ,
		
	}
	//����mypָ����ڴ汻�ͷ��ˡ�
	*myp2 = 65;//���ڴ��Ѿ����ͷţ�������ֵ�ᵼ�²���Ԥ�ϵĺ����
	//���ۣ���Զ��Ҫ��get�õ���ָ������ʼ������һ������ָ�븳ֵ��
	

	//(2.3)��Ҫ�������ָ�루this����Ϊshared ptr���أ�����enable_shared_from_this
	shared_ptr<TC>ptc1(new TC);
	//shared_ptr<TC>ptc2 = ptc1;//��������ǿ���ã�
	shared_ptr<TC>ptc2 = ptc1->getself();//�����ã�ptc1��ptc2ʧȥ����������ָ��ļ�����Ϊ1��
	//��ʱҪ��c++��׼����ߵ���ģ�壺enable_shared_from_this�Ϳ���ʹptc1��ptc2��ͨ������������Ϊ2.
	//���������洴��TC���������ָ���Լ�ͨ��TC���󷵻ص�this����ָ�붼�ǰ�ȫ�ģ�
	//enable_shared_from_this����һ����ָ�룬�����ָ���ܹ�����this��
	//�����ǵ���shared from this()�������ʱ����������ڲ�ʵ���ϵ��������weak ptr��lock����������
	//��Ҷ�֪��lock������������shared ptrָ�����+1,ͬʱ�������shared ptr��������ǹ���ԭ��







	return 0;
}