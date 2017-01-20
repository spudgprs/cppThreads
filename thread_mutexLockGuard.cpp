/*  Mutex locks with lock_guard
	std::lock_guard is a class template, which implements the RAII for mutex.
	It wraps the mutex inside it’s object and locks the attached mutex in its constructor. 
	When it’s destructor is called it releases the mutex */
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
		int get_money()
		{
			return money;
		}
		void add_money(int count)
		{
			std::lock_guard<std::mutex> lockguard(mut); //it locks automatically 
			for(int i=0;i<count;i++)
				money++;
			//it automatilcally unlocks durein the termination of function
		}
};
int calculate()
{
	wallet w1;
	std::vector<std::thread> ve;
	for(int i=0;i<5;i++)
		ve.push_back(std::thread(&wallet::add_money, &w1, 1000));
	for(int i=0;i<5;i++)
		ve[i].join();
	return w1.get_money();
}
int main()
{
	for(int i=0;i<1000;i++)
		if(calculate()!=5000)
			cout<<"Error at : "<<(i+1)<<endl;
	cout<<"Done with main"<<endl;
	return 0;
}