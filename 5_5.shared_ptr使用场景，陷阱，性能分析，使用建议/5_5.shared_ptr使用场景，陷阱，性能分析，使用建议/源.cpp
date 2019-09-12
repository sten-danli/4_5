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

//(2.3)��Ҫ�������ָ�루this����Ϊshared ptr���أ�����enable_shared_from_this
////////////////////////////////////////////////////////////////////////
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

//(2.4)����ѭ������
class CA;//����һ��CB
class CB
{
public:
	shared_ptr<CA> m_pas;
	~CB()
	{
		int test = 1;
	}
};

class CA
{
public:
	shared_ptr<CB> m_pbs;
	~CA()
	{
		int test = 1;
	}
};

int main()
{
	//(2.4)����ѭ������
	shared_ptr<CA> pca(new CA);
	shared_ptr<CB> pcb(new CB);
	pca->m_pbs = pcb;//�ȼ���ָ��CB�Ķ���������ǿ����
	pcb->m_pas = pca; //�ȼ���ָ��CA�Ķ���������ǿ����
	//Ҫ��ɹ��ͷ�������Ҫ������һ������������weak ptr�Ϳ����ˡ�



	auto ptr = myfunc(12);
	cout <<*ptr<< endl;
//
////(2.2)����get�������ص�ָ�롣
//	//��������ָ��ָ��Ķ�������Ӧ���Ǹ�ָ�루��Щ�����ӿڿ���ֻ��ʹ����ָ�룩
//	//get����������ָ�벻��delete������쳣.
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

//	//(2.4)����ѭ�����ã������ڴ�й©

	//��3.2���ƶ�����
	//shared_ptr<int>pp1 = make_shared<int>(100);
	shared_ptr<int>pp1(new int(100));
	shared_ptr<int>pp2(std::move(pp1));//�ƶ����壬�ƶ�����һ���µ�����ֻ�����p2��
	//p1�Ͳ���ָ��ö��󣨱�Ϊ�գ����ü�������1.
	
	shared_ptr<int>pp3;
	pp3 = std::move(pp2);//�ƶ���ֵ��p2ָ��գ�p3ָ��ö��������������ü�����Ϊ1.

	//���ۣ��ƶ��϶��ȸ���Ҫ�죻����Ҫ�������ü������ƶ�����Ҫ��ֱ�Ӱ���ֵ������ֵ��ʹ�á�
		//�ƶ����캯��������ƹ��캯�����ƶ���ֵ��������������ֵ�������

//�ģ�����˵����ʹ�ý���
	//������������ڴ�������⣻
	/*shared_ptr<int>p((new int), mydeleter(), mymallocator<int());*/

	//c)����ʹ��make_shared()
	shared_ptr<string>ps1(new string("lidan is c++ pro!"));//���������ڴ�
	auto ps2= make_shared<string>("Lidan is c++pro!");//ֻ����һ���ڴ�
	return 0;
}