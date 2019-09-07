#include<iostream>
using namespace std;



int main()
{
	//(2.1)unique();是否该智能指针独占莫格指向的对象，也就是若只有一个智能指针指向某个对象，则unique返回true。
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
	shared_ptr<int>pp2(new int(100));//因为pp2和pp3同时指向(new int(100))这段内存，所以当reset()指向新的内存的时候，
	//原来的内存引用计数从2变成1，同时pp1指向了新内存。
	auto pp3(pp2);//pi2引用计数会变成2；
	pp1.reset(new int(1));//释放原内存，只相信内存；
}