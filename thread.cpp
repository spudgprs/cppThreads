#include<iostream>
#include<thread>
using namespace std;
void print()
{
	cout<<"hello"<<endl;
	return 1;
}
int main()
{
	std::thread t(print);
	t.join();
	return 0;
}