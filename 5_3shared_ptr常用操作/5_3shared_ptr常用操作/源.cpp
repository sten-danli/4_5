#include<iostream>
using namespace std;



int main()
{
	//(2.1)unique();�Ƿ������ָ���ռĪ��ָ��Ķ���Ҳ������ֻ��һ������ָ��ָ��ĳ��������unique����true��
	shared_ptr<int>myp(new int(100));
	auto pint = myp;
	shared_ptr<int>myp2(myp);
	if (myp.unique())
	{
		cout << "ָ��ֱָ��һ������" << endl;
	}
	else
	{
		cout << "ָ��ָ��: " << myp.use_count() << " ������" << endl;
	}
	//(2.2)reset();�ظ�����λ/���ã�����˼
	//a��reset����������ʱ��
	//��pi��Ψһָ��ú��������ָ�룬��ô�ͷ�pi��ָ��Ķ��󣬲�����pi�ÿա�
	//��pi����Ψһָ��ö����ָ�룬��ô���Ƿ�pi��ָ��Ķ��󣬵�ָ��ö�������ü��������1��ͬʱ��pi�ÿա�
	
	shared_ptr<string>pi(new string("pro"));//һ��ָ��string��ָ�롣
	
	shared_ptr<string>pi2 = pi;//	����ָ��string��ָ�롣
	pi.reset();//RESET��pi1�ÿգ�pi2��һ��ָ��string��ָ�롣

	if (pi == nullptr)
	{
		cout << "pi ͨ��reset();�ÿա�" << endl;
	}

	//b)reset()��������һ����һ��new������ָ�룩ʱ
	//��pi��Ψһָ��ö����ָ�룬���ͷ�piָ��Ķ�����piָ���µĶ���
	shared_ptr<int>pp1(new int(100));
	pp1.reset(new int(1));//�ͷ�ԭ�ڴ棬ָ�����ڴ棻
	
	//��pi����Ψһָ��ö����ָ�룬���ͷ�piָ��Ķ��󣬵�ָ��ö�������ü��������1��ͬʱ��piָ���¶���
	shared_ptr<int>pp2(new int(100));//��Ϊpp2��pp3ͬʱָ��(new int(100))����ڴ棬���Ե�reset()ָ���µ��ڴ��ʱ��
	//ԭ�����ڴ����ü�����2���1��ͬʱpp1ָ�������ڴ档
	auto pp3(pp2);//pi2���ü�������2��
	pp1.reset(new int(1));//�ͷ�ԭ�ڴ棬ֻ�����ڴ棻
}