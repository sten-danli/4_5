#include<iostream>
using namespace std;

//shared ptrָ����ɾ����
void mydelete(string* p)//������ָ�����ü���Ϊ0���ͻ��Զ����ø�ɾ������ɾ������
{
	delete p;//��Ȼ���Լ��ṩ��ɾ������ȡ������ָ��ȱʡɾ������������������Լ�ɾ����ָ����󣨵����ü���Ϊ0ʱ��
}

int main()
{
	//(2.1)unique();�Ƿ������ָ���ռĳ��ָ��Ķ���Ҳ������ֻ��һ������ָ��ָ��ĳ��������unique����true��
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
	shared_ptr<int>px1(new int(100));//��Ϊpx1��px2ͬʱָ��(new int(100))����ڴ棬���Ե�reset()ָ���µ��ڴ��ʱ��
	//ԭ�����ڴ����ü�����2���1��ͬʱpx1ָ�������ڴ档
	auto px2(px1);//px1���ü�������2��
	px1.reset(new int(1));//�ͷ�ԭ�ڴ棬ָ�����ڴ棻
	cout << "px1 ��ָ�������ǣ� " << px1.use_count()<< endl;//px1 ��ָ�������ǣ� 1

	if (px1.unique())
	{
		cout << "unique ok!px1ָ��ֱָ��ֻ��һ������" << endl;
	}
	else
	{
		cout << "ָ��ָ��: " << px1.use_count() << " ������" << endl;
	}
	//��ָ��Ҳ����ͨ��reset�����³�ʼ��
	shared_ptr<int>p;
	p.reset(new int(1));//�ͷ�p��ָ��Ķ�����pָ���µĶ�����Ϊԭ����pΪ�գ����Ծ͵���ʲôҲû�ͷ�ֱ��ֻ�����ڴ档

//2.4)*�����ã����pָ��Ķ���
	shared_ptr<string>pstring(new string("ich bin ein string."));
	cout << "������pstring�����ǣ�"<<*pstring << endl;

//2.5) get()�����ǵ���Щ�������������������Ĳ�����Ҫ����һ�����õ���ָ�����������ָ�롣
	//p.get()����p�еı����ָ�루��ָ�룩��С��ʹ�ã��������ָ���ͷ���ָ�������ô������ص���ָ��Ҳ�ͱ����Ч��
	shared_ptr<int>mintp(new int(100));
	int* pget = mintp.get();
	*p = 45;//���У��������顣
	//delete p;���������ʱ����������Ϊ���Ѿ���ָ�뽻������ָ���ã�����ָ���Զ��ͷ��ڴ棬��
	//delete���ֶ��ͷ�������������Ԥ�ϵĴ���
	
//2.6) swap()������������ָ����ָ��Ķ���//�ܲ����á�
	shared_ptr<string>ppstring1(new string(" ppstring1:i am C++ profi!"));
	shared_ptr<string>ppstring2(new string(" ppstring2:sten are C++ profi!"));
	swap(ppstring1, ppstring2);
	cout << "ppstring 1 nach swap: "<<*ppstring1 << endl;
	ppstring1.swap(ppstring2);//Ҳ�����������á�
	cout << "ppstring 1 nach swap: " << *ppstring1 << endl;

//2.7��=nullptrr
	//a����ָ��Ķ��� ���ü�����1��������������Ϊ0�����ͷ�����ָ����ָ��Ķ���
	//b��������ָ���ÿ�
	shared_ptr<string>pnullptr(new string("lidan are c++ profi!"));
	shared_ptr<string>pnullptr1(pnullptr);//��ָ�������ȥ1�����û����һ�еĻ���ô
	pnullptr = nullptr;								//�ͷ�ԭ�ڴ棬ͬʱpnullptr����Ϊ�ա�

//2.8������ָ��������Ϊ�ж�����
	shared_ptr<string>pnamestr(new string("lidan are C++ profi."));
	pnamestr = nullptr;
	if (pnamestr)//������ָ������pnamestr��Ϊ�ж�������
	{
		cout << "pnamestrָ��һ������" << endl;
	}
	else
	{
		cout << "pnamestrָ��Ϊ�ա�" << endl;
	}

	//2.9��ָ��ɾ�����Լ���������
	//a)ָ��ɾ������
	//һ��ʱ��������ɾ����ָ��Ķ���delet��delete���������ΪĬ�ϵ���Դ������ʽ��
	//���ǿ���ָ���Լ���ɾ����ȡ��ϵͳ��Ĭ��ɾ������������ָ����Ҫɾ����ָ��Ķ���ʱ��
	//����������������Լ������ɾ������
	//shared ptrָ����ɾ���������Ƚϼ򵥣�һ��ֻ��Ҫ��������Ӿ����ɾ���������������ɡ�
	shared_ptr<string>mydeletefunc(new string("yoyo"),mydelete);//���ｫ�����Լ�д��mydeleteɾ������
	shared_ptr<string>mydeletefunc2(mydeletefunc);//������ָ��string yoyo��
	mydeletefunc2.reset();//���ͷ�ʣ��1�����ü�����mydeletefunc2Ϊnullptr
	cout << mydeletefunc2.use_count() << endl;//0
	mydeletefunc.reset();
	cout << mydeletefunc.use_count() << endl;//0














}