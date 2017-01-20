//calling threads with lambda functions
#include <iostream>
#include <thread>
using namespace std;
int main()
{
	std::thread t([]{
		cout<<"hey"<<endl;
	});
	t.join();
	return 0;
}