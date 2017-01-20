//vector of threads
#include <iostream>
#include <thread>
#include <vector>
using namespace std;
void foo()
{
	cout<<"Thread ID: "<<std::this_thread::get_id()<<endl;
}
int main()
{
	std::vector<std::thread> ve;
	for(int i=0;i<10;i++)
		ve.push_back(std::thread(foo));
	//std::for_each(ve.begin(), ve.end(), std::mem_fn(&std::thread::join));
	for(int i=0;i<ve.size();i++)
		ve[i].join(); //ve.at(i).join();
	cout<<"Done"<<endl;
	return 0;
}