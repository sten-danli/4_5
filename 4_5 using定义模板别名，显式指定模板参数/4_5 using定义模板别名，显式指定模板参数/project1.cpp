//��using �������ͻ�����ģ��
#include<iostream>
#include<map>
using namespace std;

//*��Ӧ2
//����ϣ������һ�����ͣ�ǰ���ⲿ�̶ֹ����䣬��std::map<std::string, �����Լ��ƶ�>
//��c++98ʱ��
template<typename T>
class map_s//������һ���ṹ/�ֻ࣬�ǽṹ�ĳ�Ա����public
{
public:
	typedef std::map<string,T >type;//������һ������,��stringΪ������T����Ϊֵ ��map�����������98ʱ��
	//���ǲ��ò�дһ��map_s�������������ﵽĿ�ġ�
};
///////////////////////////////////////////////

//*��Ӧ3
//��c++2011ʱ��
template <typename T>
using str_map_t = std::map<std::string, int>;//str_map_t�����͵ı�����
//using������һ�������͡������֣��������õ�.

//using�����ڶ������ͺ�����ģ����Ǻ��ǰ�����typedef�����й���,�����Ƿֱ���using��typedef������
typedef unsigned int uint_t;
using uint_t = unsigned int;

typedef std::map<std::string, int> map_t;
using map_u =std::map<std::string, int>;

typedef int (*pfuncType)(int, int);	//��typedef����һ������ָ�룻
using pfun = int (*)(int, int);		//��using����һ������ָ�룻

//*��Ӧ4
//һ������ָ�����˵��
template<typename T>
using myfunc_M=T(*)(T,T);//��������ģ�壬�Ǹ�����ָ��ģ�塣//ע��myfunc_M��������Ŷ������Ŷ��

int Realfunc(int i, int j)
{
	return 1;
}

//������ʾָ��ģ�����
//*��Ӧ5
template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}

int main()
{

	//��Ӧ4����ε��ú���ָ�롣
	myfunc_M<int> mypfunc; //myfunc_M<int>��һ������ָ�����͡�
						   //myPfunc��һ������ָ��.

	mypfunc = Realfunc;//�Ѻ�����ַ��������ָ�������
	cout << Realfunc(199, 288) << endl;//1
	

	//��Ӧ3
	str_map_t<int> mymap1;
	mymap1.insert({ "first",2 });

	//��Ӧ2
	map_s<string>::type mymapstruct;
	mymapstruct.insert({ "first","ha" });


//һ��using����ģ�����
	//��typedef����һ�����ͱ�����һ�������������ͱ�����
	typedef unsigned int uint_t;//�൱�ڸ�unsigned int�������˸�����unint_:t
	//std::map<std::string,int>

	typedef std::map <string, int>map_s_i;
	map_s_i mymap;
	mymap.insert({ "first", 1 });
	mymap.insert({ "secound", 2 });

	typedef map<string,string>map_s_s;
	map_s_s mymap2;
	mymap2.insert({ "first","firstone"});
	
	//�ܽ᣺
	//using��ʹ������ģ�壬�Ȳ�����ģ�壬Ҳ���Ǻ���ģ�壬���ǿ��Կ�����һ���µ�ģ�����ͣ�����ģ�壨ģ���������
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//������ʾָ��ģ�����
	//��Ӧ5����ʽָ��ģ������ĵ���
	auto result = sum<double,double,double>(2000000000, 20000000000);//���������ʾ�ظ������ͣ���Ϊ��ʮ���ڲ���
	//�ƶϳ�����ֻ����double����ʾ������
	cout << result << endl;

	
}

