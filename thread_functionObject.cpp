//creating threads by using function objects
#include <iostream>
#include <thread>
using namespace std;
class display{
	public:
	void operator()()
	{
		cout<<"Hello"<<":"<<endl;
	}
};
int main()
{ 
	std::thread t((display()));
	t.join();
	return 0;
}
