//	Stephen Craig
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
#include <iomanip>
#include "MyLibrarySC.h"
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
char readChar(string inputStr, char ch1, char ch2)
{
	bool vaild;
	char anyChar;

	do
	{
		vaild = true;
		cin >> anyChar;
		
		anyChar = toupper(anyChar);
		ch1 = toupper(ch1);
		ch2 = toupper(ch2);

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


Precondition: annIntRate, finYear, and loan are defined in the range > 0 && <= DBL_MAX
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

	return round(money, 2);
}

/*============================round============================================

Description: Rounds a number a certain number of places specified by numDigit
	number:		The number that needs to be rounded
	numDigit:	The place value to round to

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

/*=========================average==============================

Description: divides a number specified by divider to get the average 
	number:		The grand total 
	divider:	The number of participants recorded

Precondition: number is defined in a range >= -DBL_MAX && <= DBL_MAX
			  divider is defined in a range >= INT_MIN && <= INT_MAX

Postcondition: The average is found and returned

*/

double average(double number, int divider)
{
	double average;

	if (divider == 0)
	{
		return 0.0;
	}
	average = number / divider;

	return average;
}


void displayArray(const int list[], const int size)
{
	for (int index = 0; index < size; )
	{
		cout << setw(10) << list[index++];
		if (index % 5 == 0)
			cout << endl;
	}
	cout << endl;

}


void copyArray(int toArray[], const int fromArray[], const int size)
{
	for (int index = 0; index < size; index++)
		toArray[index] = fromArray[index];

}

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

void openIOFile(fstream& file, string fileName, ios::openmode mode) 
{
	file.open(fileName, mode); 
	
	if (file.fail()) // exit program if file open fails
	{
		cout << "\n\nERROR OPENING " << fileName << " FILE FOR "
			<< (mode == 1 ? "input" : "output") << ". \n\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
}

/*
	Some formatting codes for strftime are listed below - see help for more info:

	%a  Abbreviated weekday name
	%A  Full weekday name
	%b  Abbreviated month name
	%B  Full month name
	%c  Date and time representation appropriate for locale
	%d  Day of month as decimal number(01 – 31)
	%H  Hour in 24 - hour format(00 – 23)
	%I  Hour in 12 - hour format(01 – 12)
	%j  Day of year as decimal number(001 – 366)
	%m  Month as decimal number(01 – 12)
	%M  Minute as decimal number(00 – 59)
	%p  Current locale's A.M./P.M. indicator for 12-hour clock
	%S  Second as decimal number (00 – 59)
	%U  Week of year as decimal number, with Sunday as first day of week (00 – 53)
	%w  Weekday as decimal number (0 – 6; Sunday is 0)
	%W  Week of year as decimal number, with Monday as first day of week (00 – 53)
	%x  Date representation for current locale 111 %X  Time representation for current locale
	%y Year without century, as decimal number (00 – 99) 113 %Y Year with century, as decimal number
	%z, %Z Either the time-zone name or time zone abbreviation, depending on registry settings;
	no characters if time zone is unknown
	%%		Percent sign
	As in the printf function, the # flag may prefix any formatting code.In that case,
	the meaning of the format code is changed as follows.

	Format code  Meaning % #a, % #A, % #b, % #B, % #p, % #X, % #z, % #Z, % # % # flag is ignored.

	%#c Long date and time representation.For example : "Monday, March 16, 2020, 12:41:29". 125
	%#x Long date representation.For example : "Monday, March 16, 2020".
	%#d, %#H, %#I, %#j, %#m, %#M, %#S, %#U, %#w, %#W, %#y, %#Y
	Remove leading zeros(if any). */

string getDate(string fmtStr)
{
	const int SIZE = 50; // size of char array to store date
	char strDate[SIZE];		// c-style string - array of chars to store date
	
	time_t today;		 // represent time as a time_t integer which represents the
						 // number of seconds that have elapsed since 1/1/1970 UTC
						 // time_t good until 2038, then will need 64 bit _time64_t
	
	time(&today);		 // get time from system storing in the address of today
		
	tm thisTime;		 // a tm struct object used to store, retrieve
						 // and format various time and date components 
			
    // locatime_s function converts a time stored as a time_t value in today and stores the 
	// result in the thisTime structure of type tm 
	localtime_s(&thisTime, &today);

	// strftime function extracts time components from the tm structure thisTime
	// and returns a time formatted according to the fmtStr. The string function
    // c_str() converts a c-style string to a string class object.
	// The formatted results are stored in strDate.
	strftime(strDate, sizeof(strDate) - 1, fmtStr.c_str(), &thisTime);
		
	return strDate;
 }

// finds and returns the minimum from an array
int min(const int list[], const int size)
{
	int min = INT_MAX;
	int grade;

	for (int i = 0; i < size; i++)
	{
		grade = list[i];

		if (grade < min)
			min = grade;

	}

	return min;
}

// finds and returns the maximum from an array
int max(const int list[], const int size)
{
	int max = INT_MIN;
	int grade;

	for (int i = 0; i < size; i++)
	{
		grade = list[i];

		if (grade > max)
			max = grade;

	}

	return max;

}

// calculates and returns the average score from a student's record 
double average(const int list[], const int size)
{
	double realAverage = 0.0;

	if (size == 0)
		return 0;

	for (int i = 0; i < size; i++)
	{
		realAverage += list[i];
	}

	realAverage = average(realAverage, size);


	return realAverage;
}

// determines the grade letter based on the student's average
char grade(double gradeAverage)
{
	int score;
	char letter;

	if (gradeAverage < 0 || gradeAverage > 100)
	{
		return '*';
	}

	score = static_cast<int>(round(gradeAverage, 0));
	switch (score / 10)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		letter = 'F';
		break;
	case 6:
		letter = 'D';
		break;
	case 7:
		letter = 'C';
		break;
	case 8:
		letter = 'B';
		break;
	case 9:
	case 10:
		letter = 'A';
		break;
	default:
		letter = '*';
	}

	return letter;
}

// switches the first and last name of a person
string reverseName(string name)
{
	string::size_type pos;
	string last;
	string first;

	pos = name.find(",");

	if (pos == string::npos)
		name.insert(0, "Invalid: ");
	else
	{
		last = name.substr(0, pos);
		first = name.substr(pos + 2);
		name = first + " " + last;


	}
	return name;
}

/*=====================holdAndClearScreen======================================

Description: Clears the screen from all previous outputs

Precondition: message must be displayed

Postcondition: The screen's display shows no previous outputs 


*/

void holdAndClearScreen(string message)
{
	cout.flush();
	cout << "\n\n" << message << "\n\n";
	cin.ignore(100, '\n');
	system("cls");
}

/*==================swapV==============================

Description: Template for generic swapping of two values using the typename AnyType
			 i and j are the values to swap

Precondition: i and j receive values of AnyType by reference

Postcondition: i == j@entry and j == i@entry


*/

