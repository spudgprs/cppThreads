//thread return values
#include <iostream>
#include <thread>
#include <vector>
#include <future>
using namespace std;
int i=-1;
void func(std::promise<int> * promObj)
{
	std::mutex mut;
	//mut.lock();
	for(int j=0;j<1000;j++)
	{}
	i++;
	promObj->set_value(i);
	cout<<"Thread id is "<<std::this_thread::get_id()<<", "<<promObj;
	//mut.unlock();


}
int main()
{
	int n=0;
	cout<<"Enter the number of threads N: ";
	cin>>n;
	std::vector<std::thread> ve;
	for(int i=0;i<n;i++)
	{
		std::promise<int> promiseObj;
    	std::future<int> futureObj = promiseObj.get_future();
    	ve.push_back(std::thread(func, &promiseObj));
    	cout<<(i+1)<<" : "<<futureObj.get()<<endl;
	}
	for(int i=0;i<n;i++)
		ve[i].join();
	return 0;
}
