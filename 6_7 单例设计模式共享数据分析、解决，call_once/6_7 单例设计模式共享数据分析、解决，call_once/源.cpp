//1. 什么是单例模式
//单例模式(Singleton Pattern，也称为单件模式)，使用最广泛的设计模式之一。
//其意图是保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享。
//
//定义一个单例类：
//
//私有化它的构造函数，以防止外界创建单例类的对象；
//使用类的私有静态指针变量指向类的唯一实例；
//使用一个公有的静态方法获取该实例。

//复习：C++中类的(static)静态成员变量与(static)静态成员函数
//https://blog.csdn.net/lms1008611/article/details/81408236

//单例类写法
#include<iostream>
using namespace std;


class MyCas//这是一个单例类
{
private:
	MyCas(){}//私有化的构造函数，私有化后就不能在外面创造对象了
private:
	static MyCas* m_instance;//静态成员对象；

public:
	static MyCas* GetInstance()//定义一个静态成员函数
	{
		if (m_instance == NULL)
		{
			m_instance = new MyCas();
			static CGRdelete c1;//释放new出来m_instance.
		}
		return m_instance;
	}

	class CGRdelete//类中套类，用来释放对象
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

//静态成员变量初始化一个初始值
MyCas *MyCas::m_instance = NULL;

int main()
{
	
	MyCas* m_p = MyCas::GetInstance();//创建一个对象，返回该类的(MyCas)对象的指针；
	m_p->func();
	MyCas::GetInstance()->func();

}