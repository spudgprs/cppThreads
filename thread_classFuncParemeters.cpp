//passing paremeters to class functions thorught threads
#include <iostream>
#include <thread>
using namespace std;
class foo{
	public:
		void foo1(int a)
		{
			cout<<"hey there "<<a<<endl;
		}
};
int main()
{
	foo f;
	std::thread t(&foo::foo1, &f, 3);
	t.join();
	cout<<"Done with main"<<endl;
	return 0;
}