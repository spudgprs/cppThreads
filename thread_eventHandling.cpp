/* Suppose we are building a network based application. This application does following tasks,
	1. Perform some handshaking with server
	2. Load Data from XML files.
	3. Do processing on data loaded from XML.
	As we can see that Task 1 is not dependent on any other Tasks but Task 3 is dependent on Task 2. 
	So, it means Task 1 and Task 2 can be run in parallel by different Threads to improve the performance of application. 
	It has following disadvantages, 
	Thread will keep on acquiring the lock and release it just to check the value, 
	therefore it will consume CPU cycles and will also make Thread 1 slow, because it needs to acquire same lock to update the bool flag.
	So obviously we need a better mechanism to achieve this, like if somehow Thread 1 could just block by waiting for an Event to get signaled 
	and another Thread could signal that Event and make Thread 1 continue. It would have save many CPU cycles and gave better performance. 
	But the question is how to achieve this?
	Answer : Condtion Variables!   */
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class application
{
public:
	bool data_loaded;
	std::mutex mut;
	application()
	{
		data_loaded = false;
	}
	void main_task() //for thread 1
	{
		cout<<"Hand shaking by Thread 1"<<endl;
		//lock to check the while cond
		mut.lock(); 
		while(data_loaded!= true)
		{
			//unlcok the mutex after while check, so that threa 2 can use it;
			mut.unlock();
			//now make it to sleep for some time like 100 milliseconds
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			// again lock to check the while cond
			mut.lock();
		}
		mut.unlock(); //unlcik if it is success with while
		cout<<"Successful with loading XML data, Start processing the data by Thread 3"<<endl;
	}
	void load_data() // for thread 2
	{
		//make the thread sleep for 1 second;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cout<<"Loading XML data by Thread 2"<<endl;
		//lock the data_loadede varibale by lockk guard;
		std::lock_guard<std::mutex> lockguard(mut);
		data_loaded = true;
	}
};
int main()
{
	application app;
	cout<<"Starting the application : "<<endl;
	std::thread t1(&application::main_task, &app);
	std::thread t2(&application::load_data, &app);
	t1.join();
	t2.join();
	cout<<"Ending the application"<<endl;
	return 0;
}