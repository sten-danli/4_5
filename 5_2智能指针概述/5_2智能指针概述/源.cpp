#include<iostream>
using namespace std;


//int* pint = new int(100);
//shared_ptr<int>pint2(new int (100));//pi是一个指向值为100的int类型数据。
//shared_ptr<string>pstring(new string(5, 'a'));
//
//shared_ptr<int> makes(int value1)
//{
//	return shared_ptr<int>(new int(value1));	 
//}

//mak_shared函数：标准函数库里的函数模板。安全高效的分配何使用shared_ptr;
//他能够在动态内存（堆）stack中分配并初始化一个对象，然后返回指向此对象的share_ptr;
shared_ptr<int> pp2 = make_shared<int>(100);//这个shared_ptr指向一个值为100的整形内存，有点类似int*pi=new int(100);
																			//这玩意能够分配内存还能返回一个智能指针类型给p2；
shared_ptr<string>pp3=make_shared<string>(5, 'a');//5个字符a生成的字符串。
			//类似于string mystr（5,'a'）;



int main()
{
	shared_ptr<int> pp4 = make_shared<int>();//pp4指向一个int，int里的值初始化的值是0；
	pp4 = make_shared<int>(5889);//pp4指向一个新int，int里面保存的是5889；pp4首先释放刚才指向的值为0的内存，然后指向这个新内存的5889这个值。

	auto pp5 = make_shared<string>(8, 'a');//这个auto pp5等价于shared_ptr<string>pp3 = make_shared<string>(5, 'a'); 他能自动推断出类型。
	cout << pp5.use_count() << endl;;//显示指针之乡的数量。//1
	auto pp6(pp5);//又一新的指针指向.
	cout << pp6.use_count()<<endl;//2
	auto pp7 = pp5;
	cout << pp7.use_count() << endl;//3


	//auto  p = makes(99);//99
	//shared_ptr<int> ps = makes(99);//99
	//shared_ptr<string>bp = pstring;
	//cout << *pstring << endl;
	//cout << *p << endl;
	//cout << *bp << endl;
	//shared_ptr<int> p2 = p;
	//cout << *pint2 << endl;//999
	//cout<<p.use_count();//2
}