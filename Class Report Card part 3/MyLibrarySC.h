// Stephen Craig
// myLibrarySC.h
// #pragma once
#ifndef MY_LIBRARY_SC_H
#define MY_LIBRARY_SC_H

#include <string>
#include <limits>
#include <fstream>
using namespace std;

// enum type to store letter grades
enum GradeType {INVALID, F, D, C, B, A};

// prompts user to input a whole number between INT_MIN and INT_MAX 
int readInt(string InputStr = "Entry", int min = INT_MIN, int max = INT_MAX);

// promts the user to input a character either 'Y' or 'N'
char readChar(string inputStr = "Entry", char ch1 = 'Y', char ch2 = 'N');

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

/*=========================average==============================

Description: divides a number specified by divider to get the average
	number:		The grand total
	divider:	The number of participants recorded

Precondition: number is defined in a range >= -DBL_MAX && <= DBL_MAX
			  divider is defined in a range >= INT_MIN && <= INT_MAX

Postcondition: The average is found and returned


*/
double average(double number, int divider);

// displays an array with integer values
void displayArray(const int list[], const int size);

// displays an array with double values
void displayArray(const double list[], const int size);

// copies one array onto another array
void copyArray(int toArray[], const int fromArray[], const int size);


/*==============================openIOFile============================================================

Description: creates and opens a file which can used for either or both reading from a file for input
			 and writing to a file for output and verifies file was opened
			  file: a file stream object
			  fileName: name of file to be opened (orpossibly created)
			  mode: mode in which file is opened

Precondition: file is undefined
			  fileName is defined with a valid text file name
			  mode is defined with a valid ios class mode
			  uses fstream

Postcondition: file is opened for reading and/or writing or program is terminated

*/
void openIOFile(fstream& file, string fileName, ios::openmode mode);


string getDate(string fmtStr);

// finds and returns the minimum from an array
int min(const int list[], const int size);

// finds and returns the maximum from an array
int max(const int list[], const int size);

// calculates and returns the average from an array 
double average(const int list[], const int size);

// determines the grade letter based on the student's average
char grade(double gradeAverage);

// switches the first and last name of a person
string reverseName(string name);

void holdAndClearScreen(string message = "System Cleared");

GradeType getGrade(double gradeAverage);

char gradeTypeToChar(GradeType GPA);

#endif


