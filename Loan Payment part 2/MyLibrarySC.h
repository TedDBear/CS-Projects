// Stephen Craig
// myLibrarySC.h
// #pragma once
#ifndef MY_LIBRARY_SC_H
#define MY_LIBRARY_SC_H

#include <string>
#include <limits>
using namespace std;

// prompts user to input a whole number between INT_MIN and INT_MAX 
int readInt(string InputStr = "Entry", int min = INT_MIN, int max = INT_MAX);

// promts the user to input a character either 'Y' or 'N'
char readChar(string inputStr, char ch1, char ch2);

// prompts user to input a number between -DBL_MAX and INT_MAX
double readDouble(string InputStr = "Entry", double min = -DBL_MAX, double max = DBL_MAX);

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
double payment(double annIntRate, double finYear, int payPerYear, double loan); 

/*============================round============================================

Description: Rounds a number a certain number of places specified by numDigit

			   number: The number that needs to be rounded
			   numDigit: The place value to round to

Precondition: number is defined in a range >= -DBL_MAX && <= DBL_MAX
			  numDigit is defined in a range >= -14 && <= 14
			  uses cmath library

Postcondition: The number is rounded to numDigit's place and returned

*/
double round(double number, int numDigit);


double average(double number, int divider);

#endif


