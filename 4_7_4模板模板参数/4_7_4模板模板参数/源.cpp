//ģ��ģ��
#include<iostream>
using namespace std;
//ģ��ģ����������ʾ���Ǹ�ģ����������ģ�������������һ��ģ�壻
template<typename T,//����ģ�� 
	template <typename> typename Contrainer //�����һ��ģ��ģ������ı�̬д��
	//template<class>class Contrainer	//һ��������д
>//T��U������ģ���������Ϊ����ǰ�߶���typename�������ֳ�Ϊ����ģ�������
class myclass
{
public:
	T m_i;
	Contrainer<T> myc;//Contrainer��Ϊһ����ģ����ʹ�õģ���Ϊ��ƨ�ɺ������<>��,�������Ǹ���ģ�塣
					//���Ҫ���ף������Ҫ���Contrainer����һ��ģ��ʹ�ã���ͱ������Ū�ɡ�ģ��ģ�����������д����
	myclass()
	{
		myc.push_back(99);
	}
};

int main()
{
	
}