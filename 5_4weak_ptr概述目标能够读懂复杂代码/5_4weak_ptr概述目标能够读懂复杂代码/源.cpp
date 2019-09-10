#include<iostream>
using namespace std;


int main()
{
//一：weak ptr概述：weak ptr辅助shared ptr进行工作;
	//weak 弱，指针之意
	//强指针指的就是shared ptr，弱指针指的就是weak ptr；
	//weak ptr：也是个类模板，也是个智能指针。这个智能指针指向一个由shared ptr管理对象。但是weak ptr
    //这种指针不控制所指向的对象的生存期。
	//换取话来说weak ptr绑定到shared ptr上并不会改变shared ptr的引用计数，（跟确切的说，weak ptr的构造和析构不会增加或减少对象的引用计数）;
	//当shared ptr需要释放所定对象的时候照常释放，不管是否有weak ptr指向该对象。weak这个意思“弱”，
	//能力弱（弱共享，弱引用：共享其他的shared ptr所指向的对象），控制不了所指向对象的生存期；

	//这个弱引用（weak ptr）的作用：大家可以理解成监视shared ptr(强引用)的生命周期用的。是一种对shared ptr的扩充。
	//weak ptr不是一种独立的智能指针，不能来操作所指向的资源，所以它看起来像一个shared ptr的助手（旁观者）这种感觉。
	//weak ptr能够监视到它所指向的对象是否存在：

	//（1.1）weak ptr的创建
	//我们创建weak ptr的时候，一般使用一个shared ptr来初始化：
	auto pi = make_shared<int>(100);//shared_ptr
	weak_ptr<int>piw(pi);//piw共享pi，pi引用计数（强引用计数）不改变，但若引用计数会改变（若引用计数会从0变成1）；
	//弱引用计数才能决定对象的生存期；若引用计数并对对象生存期没有影像。
	piw = pi;//pi是一个shared ptr， 赋值给一个weak ptr，两者指向同一个内存对象；
	weak_ptr<int> piw2;
	piw2 = piw;//把weak ptr赋给两外一个weak ptr， 现在pi依然是一个强引用。piw和piw2是两个弱引用；
	//lock（）；功能就是检查weakptr所指向的对象是否存在，如果存在，那么这个lock他就返回一个指向该对象的shared ptr（指向对象的强引用计数就会加1）
	//如果它所指向的对象不存在，lock会返回一个空的shared ptr；

	pi.reset();//因为pi是唯一指向该对象的强引用智能指针，所以reset（）会释放pi所指向的对象，同时将pi置空。//加这语句后会执行else。
	auto pi2 = piw.lock();//pi2是一个shared ptr
	if (pi2 != nullptr)
	{
		//所指向的对象存在
		*pi2 = 12;
	}
	else
	{
		cout << "lock()失败，所知空间以释放。" << endl;
	}
	//总结上边这段代码：weak ptr能过半段所指向的对象是否存在，这种能力。


	//二： weak ptr常用操作
	//（2.1）use count();获取与该弱指针共享对其他shared ptr的数量，或者说获得当前所感测资源的强引用计数；
	auto pi = make_shared<int>(100);
	auto pi2(pi);//是一个sharred ptr
	weak_ptr<int>piw(pi);
	int count = piw.use_count();//2

	//(2.2)expired(): 是否过期的意思是。弱指针的use count（）为0（表示该弱指针所指向的对象已经不存在了），测返回true，
	//否则返回false，换去话说，这个函数用来判断所观测的资源是否已经被释放；
	pi.reset();
	pi2.reset();
	if (piw.expired())
	{
		cout << "pi指向空间以释放。" << endl;
	}

	//(2.3)reset();将该弱指针设置为空，不影响该对象的强引用数量，但指向该对象的弱引用数量会减少1：
	piw.reset();//pi的强引用依然为2，但piw的弱引用已经为0；


	//(2.4)lock()
	auto p1 = make_shared<int>(42);
	weak_ptr<int>pw;
	pw = p1;//可以用shared ptr给weak ptr赋值；
	if (!pw.expired())
	{
		auto p2 = pw.lock();//返回一个shared ptr，并且此时强引用计数为2；
		if (p2 != nullptr)
		{
			//TODO...
			int test = 1;
			//离开这个范围，强引用计数会恢复1
		}
	}
	else
	{
		//已经过期
		//强引用为1：
	}

	//(2.4.1)lock()一上面为例子的有意思举例：如果把weak_ptr<int>pw;调到第一行并大括号括起来，如下：执行完后将执行else语句
	weak_ptr<int>pw;
	{
		auto p1 = make_shared<int>(42);
		pw = p1;//可以用shared ptr给weak ptr赋值；
	}//当离开大括号后p1就无效了，而pw也为空。

	if (!pw.expired())//测试弱指针所指向的对象是否存在，返回true 或 false
	{
		auto p2 = pw.lock();//返回一个shared ptr，并且此时强引用计数为2；
		if (p2 != nullptr)
		{
			//TODO...
			int test = 1;
			//离开这个范围，强引用计数会恢复1
		}
	}
	else
	{
		cout << "p1指向内存已经释放。" << endl;
		//强引用为0：
	}

	//三：尺寸问题
	//weak ptr<int>pw;
	//weak ptr的尺寸和shared ptr尺寸一样大小，是罗指针的2倍。
	weak_ptr<int>pw;
	int* p;
	sizeof(p);//4个字节
	sizeof(pw);//8个字节，两个裸指针

	auto pi = make_shared<int>(100);
	weak_ptr<int>piw(pi);
	//第一个裸指针 指向的是这个智能指针所指的对象，
	//第二个裸指针 指向一个很大的数据结构（控制块），这控制块里有：
	//1：所指向的强引用计数
	//2: 所指对象的弱引用计数
	//3：其他数据，比如自定义的删除器等等：

}