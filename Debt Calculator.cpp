// Stephen Craig
// COSC 1436 Pa2 - Digit Extractor
// Created 9/8/2021
// program computes the amount that needs to be payed on a loan
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>
using namespace std;

double payment(double annIntRate, double finYear, int payPerYear, double loan);		// The amount that needs to be paid

int main()
{
	cout << fixed << setprecision(2);
	cout << "Fred owes $" << payment(6.25,3.5,12,23600) << endl;
	cout << "Sally owes $" << payment(0.0, 5, 12, 45000) << endl;
	cout << "Ryan owes $" << payment(5.75, 10.0, 4, 250000) << endl;
	cout << "Mary owes $" << payment(6.25, 5, 2, 750000) << endl;
	cout << "Billy owes $" << payment(2.5, 3, 1, 600000) << endl;
	cout << "Penelope owes $" << payment(9.65, 10, 4, 1000000) << endl;
	cout << "Alejandro owes $" << payment(0, 3.5, 1, 1000) << endl;
	cout << "Judy owes $" << payment(0, 0, 0, 0) << endl;
	cout << "Stephen owes $" << payment(7.65, 8, 3, 235675) << endl;
	cout << "Rachel owes $" << payment(4.35, 6, 2, 57643) << endl;
	cout << "Sam owes $" << payment(3.46, 3, 12, 12000) << endl;
	cout << "Lizzy owes $" << payment(5.67, 7.5, 365, 250000) << endl;
	cout << "Ryan jr. owes $" << payment(5.75, 0, 4, 250000) << endl;
	cout << "Mary jr. owes $" << payment(6.25, 5, 0, 750000) << endl;
	cout << "Billy jr. owes $" << payment(0, 3, 1, 600000) << endl;
	cout << "Stephen jr. owes $" << payment(7.65, 'a', 3, 235675) << endl;
	cout << "Rachel jr. owes $" << payment(4.35, 6, 2, -57643) << endl;
	cout << "Sam jr. owes $" << payment(-3.46, 3, 12, 12000) << endl;
	cout << "Lizzy jr. owes $" << payment(5.67, -7.5, 365, 250000) << endl;
	cout << "Fred jr. owes $" << payment(6.25, 3.5, -12, 23600) << endl;

	return 0;
}
/*========================payment=================================================================================

Description: Calculates the amount of a fixed periodic payment
	loan:		amount borrowed from the bank in USD
	finYear:	number of years financed 
	annIntRate: annual interest rate
	payPerYear:	payment periods per year


Precondition: 
	annIntRate, finYear, and loan are defined in the range >0 && <= DBL_MAX
	payPerYear is defined in the range >0 && <=365
	uses cmath library

Postcondition: The payment has been calculated and returned

*/

double payment(double annIntRate, double finYear, int payPerYear, double loan) 
{
	double money;	// The amount of the periodic payment
	double rate;	// The periodic interest rate
	double nper;	// the total amount of payments
	double i;		// This will store the pow function
	
	rate = (annIntRate/ 100) / payPerYear;		
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