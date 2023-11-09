// Stephen Craig
// COSC 1436 Pa4 - Loan Payment
// created 9/20/2021
// program computes the amount that needs to be payed on a loan
#include "myLibrarySC.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
using namespace std;

const string QUIT = "Q";


string getNameBorrower();	
string getLoanType();
double getAmountFinanced();	
double getYearsFinanced();
int getPaymentPeriod();
double getAPR();
void displayLoan(string borrower, string typeOfLoan, double loan, double years, int payPeriod, double annualIntRate, double youOwe);
int main()
{
	string name;			// name of the borrower
	string loanType;		// type of loan that is being payed off
	double loanAmount;		// the amount of the loan 
	double numberOfYears;	// the number of years financed
	int PaymentPeriod;		// the number of times to pay off a loan per year
	double APR;				// the annual interest rate
	double money;			// the amount of money that needs to be payed each month
	
	cout << "Welcome to Ted D Bank's Loan Payment Calculator.\n";
	cout << "This program will calculate how much money you owe Ted D Bank each month. \n" << endl;
	
	name = getNameBorrower();	

	while(name != QUIT)
	{
		loanType = getLoanType();	
		loanAmount = getAmountFinanced();
		numberOfYears = getYearsFinanced();
		PaymentPeriod = getPaymentPeriod();
		APR = getAPR();
		money = payment(APR, numberOfYears, PaymentPeriod, loanAmount);
		displayLoan(name, loanType, loanAmount, numberOfYears, PaymentPeriod, APR, money);
		name = getNameBorrower();	
	}

	return 0;
}

/*===================getNameBorrower===================================
Description: Prompts user to input the name of the loan borrower

Precondition: Program must start

Postcondition: The name of the Loan Borrower is recieved and returned

*/

string getNameBorrower()	
{
	string name1;

	cout << "Who is the Borrower? (or press \"" << QUIT << "\" to quit) ";
	getline(cin, name1);
	if (name1.length() > 0)
	{
		name1[0] = toupper(name1.at(0));
	}
	if (name1 == QUIT)
	{
		cout << "\nThank you for using Ted D Bank's Loan Payment Calculator\n.";
		system("pause");
		cout << "GoodBye!\n";
		exit(EXIT_SUCCESS);
	}

	return name1;
}

/*===================getLoanType===============================

Description: prompts user to input the name of the loan type

Precondition: name must be defined && != "Q"

Postcondition: name of the loan type is recieved and returned

*/

string getLoanType()
{
	string loanType1;

	cout << "What type of loan are you paying off? ";
	getline(cin, loanType1);
	if (loanType1.length() > 0)
	{
		loanType1[0] = toupper(loanType1.at(0));
	}

	return loanType1;
}

/*===================getAmountFinanced=================================
Description: Prompts user to input the amount of money they financed

Precondition: 

Postcondition: the amount financed is recieved and returned

*/

double getAmountFinanced()
{
	cout << "How much did you finance? ";
	return readDouble("Amount Financed", 1000);
}

/*====================getYearsFinanced=================================
Description: Prompts user to input the number of years financed

Precondition:  all previous functions have been executed and defined 

Postcondition: the number of years financed is recieved and returned
*/

double getYearsFinanced()
{
	cout << "How many years are you financing? ";
	return readDouble ("Years Financed", 2, 30);
}

/*===========================getPaymentPeriod==================================

Description: Prompts user to input the number of payments per year

Precondition: all previous functions have been executed and defined 

Postcondition: the number of payments per year is recieved and returned*/

int getPaymentPeriod()
{
	cout << "How many times do you pay per year? ";
	return readInt("Payment Periods", 1, 12);
}

/*===========================getPaymentPeriod==================================

Description: Prompts user to input the annual interest rate

Precondition: all previous functions have been executed and defined

Postcondition: the annual interest rate is recieved and returned*/

double getAPR()
{
	cout << "What is the annual interest rate? ";
	return readDouble ("Annual Interest Rate", 0, 100);
}

/*====================================displayLoan==================================================================
Description: Displays all of the information gathered into a chart, and tells how much the loan borrower must pay.
			 borrower:		name of the loan borrower
			 typeOfLoan:	type of loan that needs to be payed off
			 loan:			the amount of the loan
	         years:			the number of years financed
			 payPeriod:		the number of payments per year
			 annualIntRate: the annual interest rate on the loan
			 youOwe:		the amount the loan borrower owes per month

Precondition: borrower is defined && != "Q"
			  typeOfLoan is defined
			  loan is defined in the range >= 1000
			  years is defined in the range >= 2 && <= 30
			  payPeriod is defined in the range >= 1 && <= 30
			  annualIntRate is defined in the range >= 0 && <= 100
			  youOwe is defined

Postcondition: the information gathered is recieved and displayed 

*/

void displayLoan(string borrower, string typeOfLoan, double loan, double years, int payPeriod, double annualIntRate, double youOwe)
{
	const int TEXT = 25;
	const int DOLLAR = 2;
	const int VALUES = 10;

	cout << "\n\nLOAN PAYMENT REPORT FOR: " << borrower << endl;
	cout << "\nType of Loan: " << typeOfLoan << endl;

	cout << fixed << setprecision(2);
	cout << left << setw(TEXT) << "\nAmount Financed:" << right << setw(DOLLAR) << "$" << setw(VALUES) << loan << endl;

	cout << fixed << setprecision(1);
	cout << left << setw(TEXT) << "\nYears Financed:" << right << setw(DOLLAR) << " " << setw(VALUES) << years << endl;

	cout << left << setw(TEXT) << "\nPayment Period:" << right << setw(DOLLAR) << " " << setw(VALUES) << payPeriod << endl;

	cout << fixed << setprecision(2);
	cout << left << setw(TEXT) << "\nAnnual Interest Rate:" << right << setw(DOLLAR) << " " << setw(VALUES) << annualIntRate << endl;

	cout << left << setw(TEXT) << "\nAmount of Payment" << right << setw(DOLLAR) << "$" << setw(VALUES) << youOwe << endl << endl;
	
}




