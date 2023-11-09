#pragma once
#include <string>

using namespace std; 

class Plushies
{
private:
	string animal;
	int stock;
	string stuffing;
	char size;
public:
	void setAll(string, int, string, char);
	void setAnimal(string);
	void setStock(int);
	void setStuffing(string);
	void setSize(char);
	string getAnimal();
	int getStock();
	string getStuffing();
	char getSize();
	void printMemberInfo();
	Plushies();
	Plushies(string, int, string, char);
	friend ostream& operator<<(ostream& os, const Plushies& dt);
};

