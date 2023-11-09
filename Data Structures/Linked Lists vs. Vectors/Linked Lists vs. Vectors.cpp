#include <iostream>
#include "Timer.h"
#include <list>
#include <vector>

using namespace std;

int main()
{
	list<int> numberList;
	vector<int> numberVector;
	list<char> characterList;
	vector<char> characterVector;

	for (int i = 0; i < 25; i++)
	{
		numberList.push_back(i);
	}

	cout << "numberList: " << endl;
	Timer* t1 = new Timer;
	int listResult1 = numberList.front();
	delete t1;

	for (int i = 0; i < 25; i++)
	{
		numberVector.push_back(i);
	}

	cout << "\nnumberVector: " << endl;
	Timer* t2 = new Timer;
	int vectorResult1 = numberVector.front();
	delete t2;


	for (int i = 0; i < 25; i++)
	{
		characterList.push_back(static_cast<char>(i + 97));
	}

	cout << "\ncharacterList: " << endl;
	Timer* t3 = new Timer;
	int listResult2 = characterList.front();
	delete t3;

	for (int i = 0; i < 25; i++)
	{
		characterVector.push_back(static_cast<char>(i + 97));
	}

	cout << "\ncharacterVector: " << endl;
	Timer* t4 = new Timer;
	int vectorResult2 = characterVector.front();
	delete t4;


	// Vectors take slighty less time than double linked lists

	return 0;
}