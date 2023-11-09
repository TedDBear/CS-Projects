#include <iostream>
#include <algorithm>
using namespace std;

struct WishList
{
	string item;
	double price;
	double rating;

	WishList()
	{
		item = "Unknown";
		price = 0.0;
		rating = 0.0;
	};
	WishList(string item, double price, double rating)
	{
		this->item = item;
		this->price = price;
		this->rating = rating;
	}
	friend ostream& operator<<(ostream& os, const WishList& dt)
	{
		return os << dt.item << " $" << dt.price << " " << dt.rating << endl;
	};
};

int main()
{
	WishList filmEquip[5]
	{
		WishList("Camera", 427.00, 4.5),
		WishList("Computer", 1625.36, 4.8),
		WishList("Green Screen", 29.99, 3.5),
		WishList("Microphone", 52.99, 4.1),
		WishList("Adobe Premire Pro", 659.88, 5.0),
	};
	int choice = 0;
		
	do
	{
		cout << "How would you like to sort your Wish List? (or type 0 to quit)" << endl;
		cout << "1. Item Name\n"
			 << "2. Price\n"
			 << "3. Star Rating\n" << endl;
		cin >> choice;

		system("cls");

		switch (choice)
		{
		case 0: cout << "Thank you for using my program! Goodbye!" << endl;
				break;

		case 1: sort(filmEquip, filmEquip + 5,
				[](const WishList& current, const WishList& next)
				{
					return current.item < next.item;
				});

				cout << "List sorted by name (A-Z): \n" << endl;

				for (auto& film : filmEquip)
				{
					cout << film << endl;
				};
				break;

		case 2: sort(filmEquip, filmEquip + 5,
				[](const WishList& current, const WishList& next)
				{
					return current.price < next.price;
				});

				cout << "List sorted by price (low to high): \n" << endl;

				for (auto& film : filmEquip)
				{
					cout << film << endl;
				};
				break;

		case 3: sort(filmEquip, filmEquip + 5,
				[](const WishList& current, const WishList& next)
				{
					return current.rating > next.rating;
				});

				cout << "List sorted by rating (high to low): \n" << endl;

				for (auto& film : filmEquip)
				{
					cout << film << endl;
				};
				break;

		default: cout << "Error! input is invalid! please try again. \n" << endl;

		}

	} while (choice != 0);
	

	return 0;
}