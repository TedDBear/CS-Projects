#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> startTime;
	std::chrono::time_point<std::chrono::steady_clock> endTime;
	std::chrono::duration<float> runTime;
public:
	/// <summary>
	/// Start a timer with "Timer* 'name' = new Timer";
	/// end the timer with "delete 'name'"
	/// </summary>
	Timer()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		endTime = std::chrono::high_resolution_clock::now();
		runTime = endTime - startTime;
		cout << "Execution Time: ";

		cout << scientific << setprecision(2) << runTime.count() * 1'000'000'000 << " ns" << endl;
		/*if (runtime.count() > 1)
		{
			cout << "In Seconds: " << fixed << setprecision(3) << runtime.count() << endl;
		}
		else if (runtime.count() > 0.001)
		{
			cout << "In Seconds: " << runtime.count() << endl;
			cout << "In milliseconds: " << runtime.count() * 1'000 << endl;
		}
		else if (runtime.count() > 0.000001)
		{
			cout << "In milliseconds: " << runtime.count() * 1'000 << endl;
			cout << "In Nanoseconds: " << runtime.count() * 1'000'000'000 << endl;
		}
		else
		{
			cout << "In Nanoseconds: " << runtime.count() * 1'000'000'000 << endl;
		}*/
		
	}
};
