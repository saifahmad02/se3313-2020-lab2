// #include <iostream>

// int main(void)
// {
// 	std::cout << "I am a reader" << std::endl;
// }

#include <iostream>
#include "SharedObject.h"

using namespace std;

struct MyShared{
	int threadNum;
	int reportID;
	int timePassed;	//stores time passed since thread was initialized. I stopped using it. 
	int totalTime;
	int delayT;
};

int main(void)
{
	cout << "I am a reader\n";
	time_t first = time(0);
	Shared<MyShared> sharedMemory("sharedMemory");
	int count = 0;
	while (count <60){
	time_t last = time(0);
	int timer = last-first;
		cout<<"Thread Number: " <<sharedMemory->threadNum << " | Report Count: " << sharedMemory->reportID << " | Time Elapsed: " << timer << " | Delay: " << sharedMemory->delayT <<"\n";
		count++;
		sleep(1);
	}
	
}