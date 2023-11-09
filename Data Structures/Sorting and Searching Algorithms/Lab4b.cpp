#include <iostream>
#include "Timer.h"
#include <vector>
#include <algorithm>


using namespace std;
auto generateRandomVector(int elementCount)
{
	vector<int> result;
	for (int i = 0; i < elementCount; i++)
	{
		result.push_back(rand() % elementCount);

	}
	return result;
};
void ascendingSort(vector<int>& nums, const int N);
int sequentialSearch(vector<int> nums, int searchValue);
int binarySearch(vector<int> vec, int searchValue);

void printSortTimeForN(int N);

int main()
{
	printSortTimeForN(5);
	printSortTimeForN(10);
	printSortTimeForN(100);
	printSortTimeForN(1000);
	printSortTimeForN(10000);
	printSortTimeForN(100000);
	return 0;
}

void ascendingSort(vector<int>& nums, const int N)
{
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (nums[i] > nums[j])//then swap
			{
				std::swap(nums[i], nums[j]);
			}
		}
	}
}

int sequentialSearch(vector<int> nums, int searchValue)
{
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == searchValue)
		{
			return i;
		}
	}
	return -1;
}

int binarySearch(vector<int> vec, int searchValue)
{
	bool found = false;
	int first = 0;
	int last = vec.size() - 1;
	int middle;

	while (first <= last && !found)
	{
		middle = (first + last) / 2;

		if (vec[middle] == searchValue)
		{
			found = true;
		}

		else if (vec[middle] > searchValue)
		{
			last = middle - 1;
		}

		else
		{
			first = middle + 1;
		}
	}
	if (found)
	{
		return middle;
	}
	else
	{
		return -1;
	}
}

void printSortTimeForN(int N)
{
	auto vecN = generateRandomVector(N);
	auto copyVecN = vecN;

	cout << "Time for \"sort\" of " << N << " random ints: " << endl;
	Timer* tSort = new Timer;
	sort(vecN.begin(), vecN.end());
	delete tSort;
	cout << "\n\n";

	cout << "Time for \"ascendingSort\" of " << N << " random ints: " << endl;
	Timer* tAscendingSort = new Timer;
	ascendingSort(vecN, N);
	delete tAscendingSort;
	cout << "\n\n";
}
