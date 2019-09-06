//模板模板
#include<iostream>
using namespace std;
//模板模板参数：这表示这是个模板参数，这个模板参数本身，又是一个模板；
template<typename T,//类型模板 
	template <typename> typename Contrainer //这就是一个模板模板参数的变态写法
	//template<class>class Contrainer	//一般是这样写
>//T，U：叫做模板参数，因为他们前边都有typename，所以又称为类型模板参数。
class myclass
{
public:
	T m_i;
	Contrainer<T> myc;//Contrainer作为一个类模板来使用的（因为他屁股后面带着<>）,所以他是个类模板。
					//大家要明白，如果你要想把Contrainer当成一个模板使用，你就必须把它弄成“模板模板参数”这种写法。
	myclass()
	{
		myc.push_back(99);
	}
};

int main()
{
	
}