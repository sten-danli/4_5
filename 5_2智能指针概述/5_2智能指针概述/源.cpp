#include<iostream>
using namespace std;

//常规初始化（shared_ptr和new配合）

shared_ptr<int>p1;//指向int的智能指针，名p1，但目前只想为空，空指针，nullptr；
shared_ptr<int>p2(new int);//初始化一个p1指针
int* p3 = (new int(100));//pint指向一个值为100的int数据
shared_ptr<int>p4(new int (100));//p4是一个指向值为100的int类型数据。
shared_ptr<string>pstring(new string(5, 'a'));

shared_ptr<string> makes(string value1)//
{
	return shared_ptr<string>(new string(value1));	 //返回一个智能指针//可现实的用int*创建shared_ptr<int>
}

void swap(shared_ptr<int>&a, shared_ptr<int>&b)//把智能指针当作实参往函数里转递；
{
	shared_ptr<int> temp;
	temp = a;
	a = b;
	b = temp;
}

shared_ptr<int>myfunc(shared_ptr<int>& temp)//作为函数的返回值
{
	return temp;
}


int main()
{
	//mak_shared函数：标准函数库里的函数模板。安全高效的分配何使用shared_ptr;
	//他能够在动态内存（堆）stack中分配并初始化一个对象，然后返回指向此对象的share_ptr;

	shared_ptr<int> pp2 = make_shared<int>(100);//这个shared_ptr指向一个值为100的整形内存，有点类似int*pi=new int(100);
																				//这玩意能够分配内存还能返回一个智能指针类型给p2；
	shared_ptr<string>pp3 = make_shared<string>(5, 'a');//5个字符a生成的字符串。
				//类似于string mystr（5,'a'）;
	shared_ptr<int> pp4 = make_shared<int>();//pp4指向一个int，int里的值初始化的值是0；
	pp4 = make_shared<int>(5889);//pp4指向一个新int，int里面保存的是5889；pp4首先释放刚才指向的值为0的内存，然后指向这个新内存的5889这个值。

	auto pp5 = make_shared<string>(8, 'a');//这个auto pp5等价于shared_ptr<string>pp3 = make_shared<string>(5, 'a'); 他能自动推断出类型。
	cout << pp5.use_count() << endl;;//显示指针之乡的数量。//1
	auto pp6(pp5);//又一新的指针指向.
	cout << pp6.use_count()<<endl;//2
	auto pp7 = pp5;
	cout << pp7.use_count() << endl;//3

	cout << "Bitter string eingeben:"<<endl;
	string valueeingeben;
	cin >> valueeingeben;
	auto  p = makes(valueeingeben);
	cout << "Sie Haben: " << *p <<" Eingegeben."<< endl;//makes = hello


	auto a = make_shared<int>(99);
	auto b = make_shared<int>(100);
	//int a = 99;
	//int b = 100;

	//把智能指针当作实参往函数里转递
	swap(a, b);
	cout << "a = " << *a << " b = " << *b << endl;

	//作为函数的返回值；
	auto pfunc = myfunc(pp4);
	cout << "作为函数返回值为： "<<*pfunc << endl;
	cout<<"一共有都少指针指向pp4: "<<pp4.use_count()<<endl;

	//指针基础举例：
	auto ppint1 = make_shared<int>(100);
	auto ppint2 = make_shared<int>(100);
	ppint1 = ppint2;
	cout << "ppint1 指针数量为: " << ppint1.use_count() << " ppint2 指针数量为: " << ppint2.use_count() << endl;
	//给ppint1赋值会让ppint1指向ppint2指向的对象，该对象引用计数变成2，而原来pp1所指向的对象引用技术会从1变为0，
	//从而导致被释放。


	//shared_ptr<int> ps = makes(99);//99
	//shared_ptr<string>bp = pstring;
	//cout << *pstring << endl;
	
	//cout << *bp << endl;
	//shared_ptr<int> p2 = p;
	//cout << *pint2 << endl;//999
	//cout<<p.use_count();//2
}