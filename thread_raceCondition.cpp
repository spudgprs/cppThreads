//checking race condition with threads
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
class wallet
{
	public:
		wallet() : money(0){}
		int money=0;
		void add_money(int count)
		{
			for(int i=0;i<count;i++)
				money++;
		}
		int get_money()
		{
			return money;
		}
};
int raceCondCheck(int j)
{
	wallet w1;
	std::vector<std::thread> ve;
	for(int i=0;i<5;i++)
	{
		ve.push_back(std::thread(&wallet::add_money, &w1,1000));
		//cout<<(j+1)<<" : thread "<<(i+1)<<" started"<<endl;
	}
	for(int i=0;i<5;i++)
		ve[i].join();
	return w1.get_money();
}
int main()
{
	for(int i=0;i<1000;i++)
	{
		if(raceCondCheck(i)!=5000)
			cout<<"Error at i: "<<(i+1)<<endl;
	}
	return 0;
}