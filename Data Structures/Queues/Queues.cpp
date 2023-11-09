#include <iostream>
#include <iomanip>
#include "CraigQueue.h"

using std::cout;
using std::cin;
using std::endl;

const int col1 = 10, col2 = 3;

struct Job
{
	string jobID;
	int timeRemaining;

	Job()
	{
		jobID = "TBA";
		timeRemaining = -999;
	}
	Job(string jobID, int timeRemaining)
		:jobID(jobID), timeRemaining(timeRemaining)
	{
	}
	void executeInstruction()
	{
		timeRemaining--;
	}
	friend ostream& operator << (ostream& osObj, const Job& jobObj);
};
ostream& operator << (ostream& osObj, const Job& jobObj)
{
	
	osObj << left << setw(col1) << jobObj.jobID 
		  << left << setw(col2) << jobObj.timeRemaining;
	return osObj;
}
/*void processJob(CraigQueue<Job>& job)
{
	Job currentJob = (job.front());
	job.dequeue();
	currentJob.executeInstruction();
	if (currentJob.timeRemaining > 0)
	{
		job.enqueue(currentJob);
		cout << "\nUpdated job queue: " << endl;
		cout << "ID:" << "\t" << "Time Remaining" << endl;
		cout << "-----------------------" << endl;

		job.printQueue();
	}
	else 
	{
		cout << "\n......Job ID: " << currentJob.jobID
			<< " completed." << endl;
		cout << "\tThere are " << job.size()
			<< " jobs remaining.\n\n" << endl;
	}
}
*/


int main()
{
	CraigQueue<Job> runnableQueue;
	CraigQueue<Job> sleepingQueue;
	int choice = 0;
	Job newJob;
	Job currentJob;
	int jobLimit = 5;
	string jobName;
	int timeRemaining = 0;

	do 
	{
		cout << "Please select one of the following options (or type 0 to quit)" << endl;
		cout << "1 - create job and add to \"Runnable\" queue\n"
			 << "2 - display \"Runnable\" queue\n"
			 << "3 - execute job at front of a queue\n" << endl
			 << "4 - display \"Sleeping\" queue\n"
			 << "5 - move job from \"Sleeping\" to \"Runnable\" queue\n" << endl;
		try 
		{
			cin >> choice;

			if (choice < 0 || cin.fail())
			{
				throw choice;
			}
			
		}
		catch (...)
		{
			choice = 0;
		}

		switch (choice)
		{
		case 0:
			cout << "Thank you for using this program! " << endl;
			break;
		case 1:
			cout << "\nEnter a new job ID: " << endl;
			cin >> jobName;
			cout << "How much time is remaining (in ms)? ";
			cin >> timeRemaining;
			newJob.jobID = jobName;
			newJob.timeRemaining = timeRemaining;
			if (runnableQueue.size() < jobLimit)
			{
				runnableQueue.enqueue(newJob);
				cout << "The new job was successfully added to \"Runnable\" queue"
					<< "\nThere are now " << runnableQueue.size() << " jobs in queue." << endl;
			}
			else
			{
				sleepingQueue.enqueue(newJob);
				cout << "The \"Runnable\" queue has reached its limit of " << jobLimit << " jobs."
					<< "\nAdding new job to \"Sleeping\" queue" << endl;
			}
			break;
		case 2:
			cout << "Jobs in \"Runnable\" queue" << endl;
			cout << "-------------------------" << endl;
			cout << left << setw(col1) << "JobID"
				<< left << setw(col2) << "Time Remaining" << endl;
			runnableQueue.printQueue();
			break;
		case 3:
			if (runnableQueue.isEmpty())
			{
				cout << "Error! \"Runnable\" queue is empty. " << endl;
			}
			else
			{
				currentJob = runnableQueue.front();
				cout << "Executing job ID " << currentJob.jobID << endl;
				runnableQueue.dequeue();
			}
			break;
		case 4:
			cout << "Jobs in \"Sleeping\" queue" << endl;
			cout << "-------------------------" << endl;
			cout << left << setw(col1) << "JobID"
				<< left << setw(col2) << "Time Remaining" << endl;
			sleepingQueue.printQueue();
			break;
		case 5:
			if (runnableQueue.size() >= jobLimit)
			{
				cout << "Error! \"Runnable\" queue has reached its job limit.";
			}
			else
			{
				currentJob = sleepingQueue.front();
				sleepingQueue.dequeue();
				runnableQueue.enqueue(currentJob);
				cout << "Successfully moved a job from \"Sleeping\" queue to \"Runnable\" queue." << endl;
				break;
			}
		default:
			cout << "Error! input must be between 1-5." 
				 << "\nPlease Try again." << endl;
		}
		system("pause");
		system("cls");

	} while (choice != 0);
	
	return 0;
}