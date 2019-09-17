#include<iostream>
#include<thread>
using namespace std;



//void myprint(const int &i, char *pmybuf)//线程函数  //我们希望把他作为一个线程入口//不建议用引用&
void myprint(const int i, const string &pmybuf)//如果不加const在函数内可以更改pmybuf的内容并返回。
{
	//pmybuf = "you are c# pro!"; 
	cout << i << endl;
	cout << pmybuf.c_str() << endl;
	return;
}

int main()
{
	//一：传递临时对象作为线程参数
	int mvar = 1;
	int& myvary = mvar;//引用
	char mybuf[] = "this is a test!";
	thread mythread(myprint,mvar,mybuf);//但是mybuf到底是什么时候转换成string的呢//事实存在，mybuf都被回收了(main函数执行完了)，系统才用mybuf去转换string的可能，这样就会导致错误。
	//thread mythread(myprint, mvar, string(mybuf));//如果我们一定要用detach()方法的话，那我们这里直接将mybuf转换成string对象,这是一个可以保证在线程中用肯定有效的对象。
	mythread.join();//等待子线程完成。
	//mythread.detach();//更不建议用分别进程，因为当mybuf传到*pmybuf形参后，*pmybuf 和 mybuf的地址是同一地址，此时如果主线程先运行完了会释放本地址内存，于是子进程无法访问释放后的地于是出错。
	//坏就坏在detach，它会使我们的主线程很快完成推出并释放内存。
	cout << "i am c++ pro!";//等待子线程完成打印。
	return 0;

}