#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include "Blockable.h"
#include <time.h>
#include <stack>
#include <thread>
#include <unistd.h>

using namespace std;

struct MyShared{
	int threadNum;
	int reportID;
	int timePassed;
	int delayTime
};


class WriterThread : public Thread{
	public:
		int threadNumber;
		bool flag = false;	//false so that the loop doesn't break. 
		int delay;
		int reportID = 0;
		
		WriterThread(int in, int delayT):Thread(delayT*1000){
			this->threadNumber = in; 
			this->delay = delayT;
			//alters property of a memory referenced object with -> notation
			
		}

		virtual long ThreadMain(void) override{
			
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				this->reportID++; //increment report counter every cycle.
				time_t firstTime = time(0);
				sleep(delay); //sleep the thread for the specified delay
				time_t lastTime = time(0);

				int timeElapsed = lastTime - firstTime;
				sharedMemory-> threadNum = threadNumber; //set the shared memory location to the thread ID we are currently on
				sharedMemory-> timePassed = timeElapsed;
				sharedMemory-> reportID = reportID;		//update all the stuff for our shared memory location. 
				sharedMamory-> delayTime = delay;				  
				if(flag){//Exit loop to end the thread
					break;
				}
			}
		return 1;}
};


int main(void)
{
	cout << "I am a Writer\n";
	
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	
	int threadNumber = 0;
	string delayTime;
	string userInput;
	
	WriterThread * thread1; //we use this reference to create new threads in the while statement. 
	stack<WriterThread*> threadStack; 	//an empty stack. We will store the threads in here. 


	while(true){
		cout << "Do you want to create a new thread? (y/n)\n";
		//create thread using user input
		getline(cin, userInput);
		
		if (userInput == "n"){
			break;	
		}
		else{
			cout <<"What delay do u want on this thread? \n";
			threadNumber++;
			getline(cin, delayTime);
			int delayInt = stoi(delayTime);
			thread1 = new WriterThread(threadNumber, delayInt); //create a new writer thread with the thread number and the delay specified
			threadStack.push(thread1);
			
		}
	}
	//if we are no longer in the loop then we are done collecting and creating threads. Time to delete them. 
	for(auto i = 0; i < threadStack.size(); i++){
		//now we need to stop the thread. So we have to set the flag to true.
		thread1 = threadStack.top();
		thread1->flag = true;
		delete thread1;	//delete the thread! 
		threadStack.pop();	//pop the top thread. 
	}
	
	
}





