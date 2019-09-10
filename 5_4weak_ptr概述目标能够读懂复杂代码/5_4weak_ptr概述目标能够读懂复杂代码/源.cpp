#include<iostream>
using namespace std;


int main()
{
//һ��weak ptr������weak ptr����shared ptr���й���;
	//weak ����ָ��֮��
	//ǿָ��ָ�ľ���shared ptr����ָ��ָ�ľ���weak ptr��
	//weak ptr��Ҳ�Ǹ���ģ�壬Ҳ�Ǹ�����ָ�롣�������ָ��ָ��һ����shared ptr������󡣵���weak ptr
    //����ָ�벻������ָ��Ķ���������ڡ�
	//��ȡ����˵weak ptr�󶨵�shared ptr�ϲ�����ı�shared ptr�����ü���������ȷ�е�˵��weak ptr�Ĺ���������������ӻ���ٶ�������ü�����;
	//��shared ptr��Ҫ�ͷ����������ʱ���ճ��ͷţ������Ƿ���weak ptrָ��ö���weak�����˼��������
	//�������������������ã�����������shared ptr��ָ��Ķ��󣩣����Ʋ�����ָ�����������ڣ�

	//��������ã�weak ptr�������ã���ҿ������ɼ���shared ptr(ǿ����)�����������õġ���һ�ֶ�shared ptr�����䡣
	//weak ptr����һ�ֶ���������ָ�룬������������ָ�����Դ����������������һ��shared ptr�����֣��Թ��ߣ����ָо���
	//weak ptr�ܹ����ӵ�����ָ��Ķ����Ƿ���ڣ�

	//��1.1��weak ptr�Ĵ���
	//���Ǵ���weak ptr��ʱ��һ��ʹ��һ��shared ptr����ʼ����
	auto pi = make_shared<int>(100);//shared_ptr
	weak_ptr<int>piw(pi);//piw����pi��pi���ü�����ǿ���ü��������ı䣬�������ü�����ı䣨�����ü������0���1����
	//�����ü������ܾ�������������ڣ������ü������Զ���������û��Ӱ��
	piw = pi;//pi��һ��shared ptr�� ��ֵ��һ��weak ptr������ָ��ͬһ���ڴ����
	weak_ptr<int> piw2;
	piw2 = piw;//��weak ptr��������һ��weak ptr�� ����pi��Ȼ��һ��ǿ���á�piw��piw2�����������ã�
	//lock���������ܾ��Ǽ��weakptr��ָ��Ķ����Ƿ���ڣ�������ڣ���ô���lock���ͷ���һ��ָ��ö����shared ptr��ָ������ǿ���ü����ͻ��1��
	//�������ָ��Ķ��󲻴��ڣ�lock�᷵��һ���յ�shared ptr��

	pi.reset();//��Ϊpi��Ψһָ��ö����ǿ��������ָ�룬����reset�������ͷ�pi��ָ��Ķ���ͬʱ��pi�ÿա�//���������ִ��else��
	auto pi2 = piw.lock();//pi2��һ��shared ptr
	if (pi2 != nullptr)
	{
		//��ָ��Ķ������
		*pi2 = 12;
	}
	else
	{
		cout << "lock()ʧ�ܣ���֪�ռ����ͷš�" << endl;
	}
	//�ܽ��ϱ���δ��룺weak ptr�ܹ������ָ��Ķ����Ƿ���ڣ�����������


	//���� weak ptr���ò���
	//��2.1��use count();��ȡ�����ָ�빲�������shared ptr������������˵��õ�ǰ���в���Դ��ǿ���ü�����
	auto pi = make_shared<int>(100);
	auto pi2(pi);//��һ��sharred ptr
	weak_ptr<int>piw(pi);
	int count = piw.use_count();//2

	//(2.2)expired(): �Ƿ���ڵ���˼�ǡ���ָ���use count����Ϊ0����ʾ����ָ����ָ��Ķ����Ѿ��������ˣ����ⷵ��true��
	//���򷵻�false����ȥ��˵��������������ж����۲����Դ�Ƿ��Ѿ����ͷţ�
	pi.reset();
	pi2.reset();
	if (piw.expired())
	{
		cout << "piָ��ռ����ͷš�" << endl;
	}

	//(2.3)reset();������ָ������Ϊ�գ���Ӱ��ö����ǿ������������ָ��ö�������������������1��
	piw.reset();//pi��ǿ������ȻΪ2����piw���������Ѿ�Ϊ0��


	//(2.4)lock()
	auto p1 = make_shared<int>(42);
	weak_ptr<int>pw;
	pw = p1;//������shared ptr��weak ptr��ֵ��
	if (!pw.expired())
	{
		auto p2 = pw.lock();//����һ��shared ptr�����Ҵ�ʱǿ���ü���Ϊ2��
		if (p2 != nullptr)
		{
			//TODO...
			int test = 1;
			//�뿪�����Χ��ǿ���ü�����ָ�1
		}
	}
	else
	{
		//�Ѿ�����
		//ǿ����Ϊ1��
	}

	//(2.4.1)lock()һ����Ϊ���ӵ�����˼�����������weak_ptr<int>pw;������һ�в������������������£�ִ�����ִ��else���
	weak_ptr<int>pw;
	{
		auto p1 = make_shared<int>(42);
		pw = p1;//������shared ptr��weak ptr��ֵ��
	}//���뿪�����ź�p1����Ч�ˣ���pwҲΪ�ա�

	if (!pw.expired())//������ָ����ָ��Ķ����Ƿ���ڣ�����true �� false
	{
		auto p2 = pw.lock();//����һ��shared ptr�����Ҵ�ʱǿ���ü���Ϊ2��
		if (p2 != nullptr)
		{
			//TODO...
			int test = 1;
			//�뿪�����Χ��ǿ���ü�����ָ�1
		}
	}
	else
	{
		cout << "p1ָ���ڴ��Ѿ��ͷš�" << endl;
		//ǿ����Ϊ0��
	}

	//�����ߴ�����
	//weak ptr<int>pw;
	//weak ptr�ĳߴ��shared ptr�ߴ�һ����С������ָ���2����
	weak_ptr<int>pw;
	int* p;
	sizeof(p);//4���ֽ�
	sizeof(pw);//8���ֽڣ�������ָ��

	auto pi = make_shared<int>(100);
	weak_ptr<int>piw(pi);
	//��һ����ָ�� ָ������������ָ����ָ�Ķ���
	//�ڶ�����ָ�� ָ��һ���ܴ�����ݽṹ�����ƿ飩������ƿ����У�
	//1����ָ���ǿ���ü���
	//2: ��ָ����������ü���
	//3���������ݣ������Զ����ɾ�����ȵȣ�

}