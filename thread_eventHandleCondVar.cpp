#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class application
{
public:
	bool data_loaded;
	std::mutex mut;
	std::condition_variable cv;
	application()
	{
		data_loaded = false;
	}
	void load_data()
	{
		//make the thred to sleep for 1 sec pretending that it is loading the data;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout<<"Thread 2 : Loading the XML data"<<endl;
		//use lock_guard to lock the mutex and unlock it automatically at the end of the func;
		std::lock_guard<std::mutex> lockguard(mut);
		//update the data_loaded to true;
		data_loaded = true;
		//now notify conditon variable 
		cv.notify_one();//or cv.notify_all();
	}
	void main_task()
	{
		cout<<"Thread 1 : Hand Shaking"<<endl;
		//use unique_lock for condition variable over mutex
		std::unique_lock<std::mutex> ulock(mut);
		while(!data_loaded)
			cv.wait(ulock); //use cv to wait on ulock
		cout<<"Successful with loading XML data, Start processing the data by Thread 3"<<endl;
	}
};
int main()
{
	application app;
	cout<<"Opening the application"<<endl;
	std::thread t1(&application::main_task, &app);
	std::thread t2(&application::load_data, &app);
	t1.join();
	t2.join();
	cout<<"Closing the application"<<endl;
	return 0;
}