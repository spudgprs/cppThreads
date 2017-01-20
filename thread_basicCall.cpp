#include<iostream>
#include<thread>
using namespace std;
void print()
{
	cout<<"hello"<<endl;
}
int main()
{
	std::thread t(print);
	t.join();
	return 0;
}