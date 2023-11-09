#include <iostream>
#include "Timer.h"
#include <vector>
#include <algorithm>
#include <vector>
#include <chrono>

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
int sequentialSearch(vector<int> nums, int searchValue);
int binarySearch(vector<int> vec, int searchValue);

int main()
{
	vector<int> evenVector;
	int biggestNumber = 50;
	int counter = 0;
	int searchValue;
	srand(time(0));

	for (int i = 0; i <= biggestNumber; i++)
	{
		if (i % 2 == 0)
		{
			evenVector.push_back(i);
		}
		
	}

	cout << "Even number vector from 0 to " << biggestNumber << endl; 
	for (int i = 0; i < evenVector.size(); i++)
	{
		cout << evenVector[i] << " ";
	}

	cout << endl;

	while (counter < 5)
	{
		searchValue = rand() % biggestNumber;
		if (searchValue % 2 != 0)
		{
			searchValue += 1;
		}

		cout << "\nSearching for " << searchValue << endl;
		
		cout << "\nTotal number of guesses for binary search: " << binarySearch(evenVector, searchValue) << endl;
		cout << "Total number of guesses for sequential search: " << sequentialSearch(evenVector, searchValue) << endl;

		counter++;
	}


	return 0;
}

int sequentialSearch(vector<int> nums, int searchValue)
{
	int numGuesses = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == searchValue)
		{
			return numGuesses;
		}
		numGuesses++;
	}
	return -1;
}

int binarySearch(vector<int> vec, int searchValue)
{
	bool found = false;
	int numGuesses = 0;
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
		numGuesses++;
	}
	if (found)
	{
		return numGuesses;
	}
	else
	{
		return -1;
	}
}

