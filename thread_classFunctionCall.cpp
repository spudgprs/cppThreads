//calling a funtion of a class through thread
#include <iostream>
#include <thread>
using namespace std;
class hello{
	public:
		void prin(int c) 
		{
			cout<<"hello"<<c<<": "<<endl;
		}
};
int main()
{
	hello h1;
	std::thread t(&hello::prin, &h1);
	t.join();
	return 0;
}