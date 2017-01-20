//passing paremeters to afunction with threads
#include <iostream>
#include <thread>
using namespace std;
void foo(int n)
{
	cout<<"function call value : "<<n<<endl;
}
int main()
{
	std::thread t(foo,2);
	t.join();
	return 0;
}