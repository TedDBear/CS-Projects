// Stephen Craig
// COSC 1436 Pa2 - Digit Extractor
// Created 8/30/2021
// program computes and outputs the individual digits of a number up to 3 digits long
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

const int QUIT = 0;		// value to end the program

int readInt(string inputStr = "3-digit number", int min = INT_MIN, int max = INT_MAX);
double readDouble(string inputStr = "3-digit number", double min = -DBL_MIN, double max = DBL_MAX);

int main()
{
	int threeNumberDigit;	// a number up to three digits
	bool valid;
	cout << "Digit Extractor\n\n";
	cout << "This program will Extract up to 3 Digits beginning with the 100's place value.";

	cout << "\n\nEnter a 3-digit number between 1 and 999 (or enter 0 to exit the program): ";
		threeNumberDigit = readInt("3-digit number", 0,999);
	//	threeNumberDigit = readDouble();

	while (threeNumberDigit != QUIT)
	{
		int hundred = threeNumberDigit / 100 % 10;	// The left most digit of a three digit number
		int ten = threeNumberDigit / 10 % 10;	// The middle digit of a three digit number
		int one = threeNumberDigit % 10;	// The right most digit of a three digit number

		cout << "The digits in the number " << threeNumberDigit << " are "
			<< hundred << ", "
			<< ten << ", and "
			<< one << ". "
			<< endl;

		cout << "\nEnter another 3-digit number between 1 and 999 (or enter 0 to exit the program): ";
			threeNumberDigit = readInt("3-digit number", 0,999);
		//	threeNumberDigit = readDouble("3-digit number");
	}
	cout << "\nThank You for using The Digit Extractor.  Goodbye!";// Tells the user that the program ended

	return 0;
}

int readInt(string inputStr, int min, int max)
{
	bool vaild;
	int anyInt;
	do
	{
		vaild = true;
		cin >> anyInt;

		vaild = anyInt >= min && anyInt <= max;

		if (cin.fail() || /*cin.peek() != '\n'*/ !isspace(cin.peek()) || !vaild)	// This will tell the user if they inputted an invaild number 	
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nError. " << inputStr << " must be a whole number between "
				<< min << " and " << max << "\n";
			cout << "Please Try Again: ";
			vaild = false;
		}
	} while (!vaild);

	cin.ignore(100, '\n');
	return anyInt;
}

double readDouble(string inputStr, double min, double max)
{
	bool vaild;
	double anyDouble;
	do
	{
		vaild = true;
		cin >> anyDouble;

		vaild = anyDouble >= min && anyDouble <= max;

		if (cin.fail() || !isspace(cin.peek()) || !vaild)	// This will tell the user if they inputted an invaild number 	
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nError. " << inputStr << " must be a number between "
				<< min << " and " << max << "\n";
			cout << "Please Try Again: ";
			vaild = false;
		}
	} while (!vaild);

	cin.ignore(100, '\n');
	return anyDouble;
}
