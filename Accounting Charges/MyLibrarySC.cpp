//	Stephen Craig
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
#include <iomanip>
using namespace std;

// the number to input for the amount of time consulting 
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

// a charatcer to input for a yes/no answer
char readChar(string inputStr = "Entry" , char ch1 = 'Y', char ch2 = 'N')
{
	bool vaild;
	char anyChar;

	do
	{
		vaild = true;
		cin >> anyChar;
		
		anyChar = toupper(anyChar);

		vaild = anyChar == ch1 || anyChar == ch2;

		if (cin.fail() || !isspace(cin.peek()) || !vaild)	// This will tell the user if they inputted an invaild number 	
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nError. " << inputStr << " must be either "
				<< ch1 << " or " << ch2 << "\n";
			cout << "Please Try Again: ";
			vaild = false;
		}
	} while (!vaild);

	cin.ignore(100, '\n');
	return anyChar;
}

// the number to input for the amount of annual income
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
			cout << "\nError. " << inputStr << " must be a number between " << setprecision(2)
				<< (min < -1e6 || min > -1e-6 && min < 1e-6 && min != 0 || min > 1e6 ? scientific : fixed) 
				<< min << " and " 
				<< (max < -1e6 || max > -1e-6 && max < 1e-6 && max != 0 || max > 1e6 ? scientific : fixed) 
				<< max << "\n";
			cout << "Please Try Again: ";
			vaild = false;
		}
	} while (!vaild);

	cin.ignore(100, '\n');
	return anyDouble;
}

/*========================payment================================================

Description: Calculates the amount of a fixed periodic payment
	loan:		amount borrowed from the bank in USD
	finYear:	number of years financed
	annIntRate: annual interest rate
	payPerYear:	payment periods per year


Precondition:
	annIntRate, finYear, and loan are defined in the range > 0 && <= DBL_MAX
	payPerYear is defined in the range > 0 && <= 365
	uses cmath library

Postcondition: The payment has been calculated and returned

*/

double payment(double annIntRate, double finYear, int payPerYear, double loan)
{
	double money;	// The amount of the periodic payment
	double rate;	// The periodic interest rate
	double nper;	// the total amount of payments
	double i;		// This will store the pow function

	rate = (annIntRate / 100) / payPerYear;
	nper = finYear * payPerYear;

	if (rate == 0)		// interest rate is 0 
	{
		money = loan / nper;
	}
	else
	{
		i = pow(1 + rate, nper);		// The pow call results for multiple use
		money = rate * i / (i - 1) * loan;
	}

	return money;
}

/*============================round============================================

Description: Rounds a number a certain number of places specified by numDigit

			   number: The number that needs to be rounded
			   numDigit: The place value to round to

Precondition: number is defined in a range >= -DBL_MAX && <= DBL_MAX
			  numDigit is defined in a range >= -14 && <= 14
			  uses cmath library

Postcondition: The number is rounded to numDigit's place and returned

*/

double round(double number, int numDigit)
{
	double roundedNumber;
	double place;

	place = pow(10.0, numDigit);


	roundedNumber = floor(fabs(number) * place + 0.5) / place;

	if (number < 0)
	{
		roundedNumber = -roundedNumber;
	}

	return roundedNumber;
}