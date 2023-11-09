#pragma once
#include <vector>

using namespace std;

template <typename T>
int sequentialSearch(vector<T> vec, T searchValue)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == searchValue)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
int binarySearch(vector<T> vec, T searchValue)
{
	bool found;
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
