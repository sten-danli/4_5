//1. ʲô�ǵ���ģʽ
//����ģʽ(Singleton Pattern��Ҳ��Ϊ����ģʽ)��ʹ����㷺�����ģʽ֮һ��
//����ͼ�Ǳ�֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㣬��ʵ�������г���ģ�鹲��
//
//����һ�������ࣺ
//
//˽�л����Ĺ��캯�����Է�ֹ��紴��������Ķ���
//ʹ�����˽�о�ָ̬�����ָ�����Ψһʵ����
//ʹ��һ�����еľ�̬������ȡ��ʵ����

//��ϰ��C++�����(static)��̬��Ա������(static)��̬��Ա����
//https://blog.csdn.net/lms1008611/article/details/81408236

//������д��
#include<iostream>
using namespace std;


class MyCas//����һ��������
{
private:
	MyCas(){}//˽�л��Ĺ��캯����˽�л���Ͳ��������洴�������
private:
	static MyCas* m_instance;//��̬��Ա����

public:
	static MyCas* GetInstance()//����һ����̬��Ա����
	{
		if (m_instance == NULL)
		{
			m_instance = new MyCas();
			static CGRdelete c1;//�ͷ�new����m_instance.
		}
		return m_instance;
	}

	class CGRdelete//�������࣬�����ͷŶ���
	{
	public:
		~CGRdelete()
		{
			if (MyCas::m_instance)
			{
				delete MyCas::m_instance;
				MyCas::m_instance = NULL;
			}
		}

	};
	void func()
	{
		cout << "Test" << endl;
	}
};

//��̬��Ա������ʼ��һ����ʼֵ
MyCas *MyCas::m_instance = NULL;

int main()
{
	
	MyCas* m_p = MyCas::GetInstance();//����һ�����󣬷��ظ����(MyCas)�����ָ�룻
	m_p->func();
	MyCas::GetInstance()->func();

}