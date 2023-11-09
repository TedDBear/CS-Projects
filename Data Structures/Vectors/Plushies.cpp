#include "Plushies.h"
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

void Plushies::setAll(string plushieType, int inventory, string filling, char sizeLetter)
{
	animal = plushieType;
	stock = inventory;
	stuffing = filling;
	size = sizeLetter;
}

void Plushies::setAnimal(string plushieType)
{
	animal = plushieType;
}

void Plushies::setStock(int inventory)
{
	stock = inventory;
}

void Plushies::setStuffing(string filling)
{
	stuffing = filling;
}

void Plushies::setSize(char sizeLetter)
{
	switch (toupper(sizeLetter))
	{
	case 'S':
	case 'M':
	case 'L':
		size = toupper(sizeLetter);
	default:
		size = '0';
	}
}

string Plushies::getAnimal()
{
	return animal;
}

int Plushies::getStock()
{
	return stock;
}

string Plushies::getStuffing()
{
	return stuffing;
}

char Plushies::getSize()
{
	return size;
}

void Plushies::printMemberInfo()
{
	cout << "\nPlushies: " << endl;
	cout << "What animal is the plushie? " << animal << endl;
	cout << "How many are in stock? " << stock << endl;
	cout << "What is the plushie filled with? " << stuffing << endl;
	cout << "What is the plushie's size? " << size << endl;
}

Plushies::Plushies()
{
	animal = "Figment";
	stock = 0;
	stuffing = "clouds";
	size = '0';
}

Plushies::Plushies(string type, int inventory, string filling, char letterSize)
{
	animal = type;
	stock = inventory;
	stuffing = filling;
	size = letterSize;
}

ostream& operator<<(ostream& os, const Plushies& plush)
{
	os << "\nWhat animal is the plushie? " << plush.animal << endl
	   << "How many are in stock? " << plush.stock << endl 
	   << "What is the plushie filled with? " << plush.stuffing << endl 
	   << "What is the plushie's size? " << plush.size << endl;

	return os;
}
