// Stephen Craig
// COSC 1436 PA5 - Accounting Charges
// created 10/4/2021
// program computes the amount a client needs to pay after a certain time of consulting 
#include "MyLibrarySC.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
using namespace std;

// gets information on the client's name, income, and the amount of time consulting
void getClientInfo(string& clientName, double& annualIncome, int& consultTime);
// calulates and displays how much the client owes
double getCharges(double annualIncome1, int consultTime1);

int main()
{
	char answer;		// determines if their is a client  
	string name;		// the name of the client
	double income;		// the amount in U.S. currency the client makes per year
	int time;			// the amount of time the client consulted
	double charge;		// the amount the client owes the firm in U.S. currency

	cout << "Do you have a client? (Y/N): ";
	answer = readChar();

	while (answer == 'Y')
	{
		getClientInfo(name, income, time);

		charge = getCharges(income, time);

		cout << name << " Owes the Firm $" << charge << endl;

		cout << "\nDo you have another client? (Y/N): ";
		answer = readChar();
	}

	cout << "\nThank you for your time.\n";
	system("pause");
	cout << "GoodBye!\n";

	return 0;
}

// Gathers the client's information such as name, income, and time consulting
void getClientInfo(string& clientName, double& annualIncome, int& consultTime)
{
	cout << "What is the client's name? ";
	getline(cin, clientName);
	if (clientName.length() > 0)
	{
		clientName[0] = toupper(clientName.at(0));
	}

	cout << "What is their annual income? ";
	annualIncome = readDouble("Income", 0, 1000000);

	cout << "How long did they consult for (in minutes)? ";
	consultTime = readInt("Time", 0, 300);
}

/*======================getCharges==============================================

Description: calculates the amount owed from a client
	annualIncome1: The amount of money that a client makes per year
	consultTime1: The amount of time a client consults with a finacial advisor

Precondition: annualIncome1 is defined in the range >= 0 && <= 1,000,000
			  consultTime is defined in the range >= 0 && <= 300

Postcondition: The price is calculated and returned

*/

double getCharges(double annualIncome1, int consultTime1)
{ 
	double price;						// the amount that the client has to pay
	bool lowIncome = false;				// determines if the client is of low-income
	const double FEE = 70.00;			// the normal rate per hour in U.S. currency
	const double POVERTY = 25000.00;	// the income that indicates the client is low-income
	const double POVERTY_RATE = 40;		// the rate for low-income clients after their free time
	const int POVERTY_TIME = 30;		// the amount of time that is free for a low-income clients in minutes
	const double RATE = 70;				// the rate for a normal client after their free time
	const int TIME = 20;				// the amount of time that is free for a normal client in minutes

	if (annualIncome1 <= 25000.00)
		lowIncome = true;

	if (lowIncome)
	{
		price = FEE * (POVERTY_RATE / 100) * ((consultTime1 - POVERTY_TIME) / 60.0);
	}
	else
	{
		price = FEE * (RATE / 100) * ((consultTime1 - TIME) / 60.0);
	}
	
	if (price < 0)
		price = 0;
	

	return round(price, 2);
}






