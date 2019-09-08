#include<iostream>
using namespace std;

//shared ptr指定的删除器
void mydelete(string* p)//当智能指针引用计数为0，就会自动调用该删除器来删除对象。
{
	delete p;//既然你自己提供了删除器来取代智能指针缺省删除器，你就有义务来自己删除所指向对象（当引用计数为0时）
}
///////////////////////////////////////
class A
{
public:
	A(){}
	~A(){}
};
///////////////////////////////////////

int main()
{
	//(2.1)unique();是否该智能指针独占某个指向的对象，也就是若只有一个智能指针指向某个对象，则unique返回true。
	shared_ptr<int>myp(new int(100));
	auto pint = myp;
	shared_ptr<int>myp2(myp);
	if (myp.unique())
	{
		cout << "指针直指向一个对象" << endl;
	}
	else
	{
		cout << "指针指向: " << myp.use_count() << " 个对象" << endl;
	}
	//(2.2)reset();回复（复位/重置）的意思
	//a）reset不带参数的时候
	//若pi是唯一指向该函数对象的指针，那么释放pi所指向的对象，并将将pi置空。
	//若pi不是唯一指向该对象的指针，那么不是放pi所指向的对象，但指向该对象的引用计数会减少1，同时将pi置空。
	
	shared_ptr<string>pi(new string("pro"));//一个指向string的指针。
	
	shared_ptr<string>pi2 = pi;//	两个指向string的指针。
	pi.reset();//RESET后pi1置空，pi2有一个指向string的指针。

	if (pi == nullptr)
	{
		cout << "pi 通过reset();置空。" << endl;
	}

	//b)reset()带参数（一般是一个new出来的指针）时
	//若pi是唯一指向该对象的指针，则释放pi指向的对象，让pi指向新的对象。
	shared_ptr<int>pp1(new int(100));
	pp1.reset(new int(1));//释放原内存，指向新内存；
	
	//若pi不是唯一指向该对象的指针，则不释放pi指向的对象，但指向该对象的引用计数会减少1，同时让pi指向新对象。
	shared_ptr<int>px1(new int(100));//因为px1和px2同时指向(new int(100))这段内存，所以当reset()指向新的内存的时候，
	//原来的内存引用计数从2变成1，同时px1指向了新内存。
	auto px2(px1);//px1引用计数会变成2；
	px1.reset(new int(1));//释放原内存，指向新内存；
	cout << "px1 的指针数量是： " << px1.use_count()<< endl;//px1 的指针数量是： 1

	if (px1.unique())
	{
		cout << "unique ok!px1指针直指向只有一个对象。" << endl;
	}
	else
	{
		cout << "指针指向: " << px1.use_count() << " 个对象。" << endl;
	}
	//空指针也可以通过reset来重新初始化
	shared_ptr<int>p;
	p.reset(new int(1));//释放p所指向的对象，让p指向新的对象，因为原来的p为空，所以就等于什么也没释放直接只相信内存。

//2.4)*解引用：获得p指向的对象
	shared_ptr<string>pstring(new string("ich bin ein string."));
	cout << "解引用pstring内容是："<<*pstring << endl;

//2.5) get()；考虑到有些函数（第三方函数）的参数需要的是一个内置的裸指针而不是智能指针。
	//p.get()返回p中的保存的指针（裸指针），小心使用，如果智能指针释放了指向对象，那么这个返回的裸指针也就变得无效。
	shared_ptr<int>mintp(new int(100));
	int* pget = mintp.get();
	*p = 45;//可行，但不建议。
	//delete p;会出错，这是时候不能用是因为你已经把指针交给智能指针用，智能指针自动释放内存，而
	//delete是手动释放这样产生不可预料的错误。
	
//2.6) swap()交换两个智能指针所指向的对象//很不常用。
	shared_ptr<string>ppstring1(new string(" ppstring1:i am C++ profi!"));
	shared_ptr<string>ppstring2(new string(" ppstring2:sten are C++ profi!"));
	swap(ppstring1, ppstring2);
	cout << "ppstring 1 nach swap: "<<*ppstring1 << endl;
	ppstring1.swap(ppstring2);//也可以这样调用。
	cout << "ppstring 1 nach swap: " << *ppstring1 << endl;

//2.7）=nullptrr
	//a）将指向的对象 引用计数减1，若果引用数变为0，测释放智能指针所指向的对象。
	//b）将智能指针置空
	shared_ptr<string>pnullptr(new string("lidan are c++ profi!"));
	shared_ptr<string>pnullptr1(pnullptr);//把指针计数减去1，如果没有至一行的话那么
	pnullptr = nullptr;								//释放原内存，同时pnullptr设置为空。

//2.8）智能指针名字作为判断条件
	shared_ptr<string>pnamestr(new string("lidan are C++ profi."));
	pnamestr = nullptr;
	if (pnamestr)//用智能指针名字pnamestr作为判断条件。
	{
		cout << "pnamestr指向一个对象。" << endl;
	}
	else
	{
		cout << "pnamestr指向为空。" << endl;
	}

	//2.9）指定删除器以及数组问题
	//a)指定删除器；
	//一定时机帮我们删除所指向的对象；delet将delete运算符号作为默认的资源析构方式。
	//我们可以指定自己的删除器取代系统的默认删除器，当智能指针需要删除所指向的对象时，
	//编译器会调用我们自己定义的删除器。
	//shared ptr指定的删除器方法比较简单，一般只需要在数中添加具体的删除器函数的名即可。
	/*
	shared_ptr<string>mydeletefunc(new string("yoyo"),mydelete);//这里将调用自己写的mydelete删除器(mydelete函数在main上面）
	shared_ptr<string>mydeletefunc2(mydeletefunc);//两个都指向string yoyo；
	mydeletefunc2.reset();//被释放剩下1个引用计数，mydeletefunc2为nullptr
	cout << mydeletefunc2.use_count() << endl;//0
	mydeletefunc.reset();
	cout << mydeletefunc.use_count() << endl;//0
	*/

	//2.9.1 删除器可以不用函数方法，也可以是用lamda表达式：注意lamda表达式的写法；
	shared_ptr<string>mydeletefunc(new string("yoyo"), [](string* stringp) {
		delete stringp;
		});

	//有些情况，默认删除器处理不了的时候（当用shared ptr管理动态数组），需要我们提供指定的删除器：演示如下
	//我们new一个数组：然后用lamda表达式删除，我们很少用shared ptr中用数组，因为有很多处理数组的容器很好用。
	shared_ptr<int>plamda(new int[10], [](int* p) {
		delete[]p;
		});

	//shared_ptr<A>pA(new A[10]);//这里系统出现异常，因为系统释放pA是delete pA所指向的裸指针而不是[]pA,
	//这这种情况下我们需要写自己的删除器，如下：
	shared_ptr<A>pAlamda(new A[10], [](A* p) {
		delete[]p;
		});

	cout << "pAlamda的指针计数为："<<pAlamda.use_count() << endl;

	//2.9.2还可以用default delete来做删除器，default delete是用标准库里的模板类。
	shared_ptr<A>defaultdelete(new A[10], default_delete<A[]>());//旧写法
	//A[]这个[]代表数组，我们做的很多的工作就是为了数组的正常释放，C走到17版本的时候我们已经可以不用这样写，
	//按如下在定义数组的时候加上一个[]就可以了:
	shared_ptr<string[]>defaultdelete2(new string[10]);//新写法，如果这样写编译器就知道你要删除的是数组，就不自己写删除器了。shared_ptr<A[]>
	defaultdelete2[0] = "i";
	defaultdelete2[1] = "am";
	defaultdelete2[2] = "c++ pro!";

	for (auto i = 0; i <= sizeof(defaultdelete2); i++)
	{
		cout << defaultdelete2[i] << endl;
	}





}