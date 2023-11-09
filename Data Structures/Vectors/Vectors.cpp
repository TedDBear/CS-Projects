#include <iostream>
#include "CraigVector.h"
#include "Plushies.h"

using namespace std;

int main()
{
	CraigVector<Plushies> stuffedAnimals;
	CraigVector<string> words;

	Plushies teddyBear("Teddy Bear", 43, "Cotton", 'S');
	Plushies beanieBabies("Beanie Babies", 12, "Pellets", 'S');
	Plushies pillowPet("Pillow Pet", 2, "Polyester", 'M');

	cout << "Stuffed Animal Vector" << endl;
	cout << "-----------------------------" << endl;

	cout << "Initial size: " << stuffedAnimals.getSize() << endl;
	cout << "Initial capacity: " << stuffedAnimals.getCapacity() << endl;

	stuffedAnimals.push_back(teddyBear);
	cout << "\nMemory Allocated" << endl;
	stuffedAnimals.push_back(pillowPet);
	cout << "Memory Allocated" << endl;
	stuffedAnimals.insertAt(beanieBabies, 2);
	cout << "Memory Allocated" << endl;
	

	cout << "\nnew size: " << stuffedAnimals.getSize() << endl;
	cout << "new capacity: " << stuffedAnimals.getCapacity() << endl;

	stuffedAnimals.print();

	cout << "Words Vector" << endl;
	cout << "-----------------------------" << endl;

	words.allocate(5);

	words.push_back("Apple");
	words.push_back("Windows");
	words.push_back("BlackBerry");
	words.push_back("Android");
	words.push_back("Rubber Duck");
	words.insertAt("Intel", 2);

	cout << "Initial list of words: " << endl;
	words.print();

	words.pop_back();

	cout << "\nNew list of words after popping: " << endl;
	words.print();

	words.deleteAt(3);

	cout << "\nNew list of words after deleting \"BlackBerry\": " << endl;
	words.print();

	words.bringToFront(2);

	cout << "\nList of words after using bringToFront function: " << endl;
	words.print();

	return 0;
}