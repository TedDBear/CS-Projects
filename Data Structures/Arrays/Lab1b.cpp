#include <iostream>
#include "CraigArray.h"

using namespace std;

int main()
{
	CraigArray <char, 4> letterList;
	CraigArray <int, 20> countToTwenty;
	CraigArray <string, 3> test;

	cout << "LetterList: " << endl;
	for (int i = 0; i < letterList.getElementCount(); i++)
	{
		letterList.modifyElement(i, static_cast<char>(i + 97));
		letterList.printAnElement(i);
		if (i % 2 == 0 and i != 0)
		{
			letterList.swap(i - 2, i);
		}
	}
	cout << endl;
	cout << "CountToTwenty: " << endl;
	for (int i = 0; i < countToTwenty.getElementCount(); i++)
	{
		countToTwenty.modifyElement(i, i + 1);
		cout << countToTwenty.getElementAt(i) << endl;

	}
	cout << endl;
	cout << "Test (with strings): " << endl;
	for (int i = 0; i < test.getElementCount(); i++)
	{
		test.modifyElement(i, "ha");
		cout << test[i] << endl;
	}
	cout << endl;

	cout << "Using printArray to print all of the elements in each list: " << endl;
	letterList.printArray();
	cout << "(swapped c and a to different positions)" << endl;
	countToTwenty.printArray();
	test.printArray();
	return 0;
}