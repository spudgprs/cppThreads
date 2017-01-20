#include <iostream>
#include <thread>
using namespace std;
void id()
{
	cout<<"ID : "<<std::this_thread::get_id()<<endl;
}
int main()
{
	std::thread t1(id);
	std::thread t2(id);
	if(t1.get_id()==t2.get_id())
		cout<<"Both are euqal"<<endl;
	cout<<"T1 ID: "<<t1.get_id()<<endl;
	cout<<"T2 ID: "<<t2.get_id()<<endl;
	t1.join();
	t2.join();
	return 0;
}