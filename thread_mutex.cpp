/* 	using mutex for threads
	But what if we forgot to unlock the mutex at the end of function. 
	In such scenario, one thread will exit without releasing the lock and other threads will remain in waiting.
	This kind of scenario can happen in case some exception came after locking the mutex. 
	To avoid such scenarios we should use std::lock_guard. */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
class wallet
{
public:
	int money;
	std::mutex mut;
	wallet():money(0){}
	void add_money(int count)
	{
		mut.lock();
		for(int i=0;i<count;i++)
			money++;
		mut.unlock();
	}
	int get_money()
	{
		return money;
	}
};
int callThread()
{
	wallet w1;
	std::vector<std::thread> ve;
	for(int i=0;i<5;i++)
		ve.push_back(std::thread(&wallet::add_money, &w1,1000));
	for(int i=0;i<5;i++)
		ve[i].join();
	return w1.get_money();
}
int main()
{
	for(int i=0;i<1000;i++)
	{
		if(callThread()!=5000)
			cout<<"Error at "<<(i+1)<<endl;
	}
	cout<<"End of main"<<endl;
	return 0;
}