// Stephen Craig
// COSC 1436 Pa6 - Loan Payment w/ File processing
// created 10/6/2021
// program displays information about a loan from a text file
#include "myLibrarySC.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
using namespace std;

void displayHeadingReport(ostream& out);
void readRecordLine(ifstream& fin, string& borrowerName, string& loanType, double& intRate, double& financedYears, int& paymentPeriod, double& loan);
void displayRecordLine(ostream& out, string borrowerName, string loanType, double loan, double financedYears, int paymentPeriod, double intRate, double perFin, double perPay, double perInt);
void displayTotalValues(ostream& out, int recordCount, double totalFinance, double totalPayments, double totalInterest);

const int WORDS = 20, LOAN = 12, MONEY = 10, PAYMENT = 11, PAYMENT_WORD = 13, MONEY_WORDS = 12, INTEREST = 11, YEARS = 10, TERMS = 8,
		  TOTAL$ = 42, $ = 43, TOTAL_FIN = 10, TOTAL_PAY = 11, TOTAL_INT = 10, DOLLAR = 2;

int main()
{
	ifstream fin;										 // input file stream
	ofstream fout;										 // output file stream
	int recordCount = 0;								 // counts the amount of records in the file
	string inFileName = "Loan Data2 F21.txt";			 // name of the input file
	string outFileName = "Loan Payment Report 2.txt";	 // name of the output file
	string name;										 // name of the borrower
	string loanType;									 // type of loan that is being payed off
	double loanAmount;									 // the amount of the loan in U.S. currency
	double numberOfYears;								 // the number of years financed
	int PaymentPeriod;									 // the number of times to pay off a loan per year
	double APR;											 // the annual interest rate
	double personalFinance;								 // the amount of money that needs to be payed each month by an individual
	double personalPayments;							 // the total amount of money that needs to be payed by an individual
	double personalInterest;							 // the amount of interest in dollars that accumulated from an individual
	double totalFinance = 0;							 // the amount of money that needs to be payed each month from all of the clients
	double totalPayments = 0;							 // the total amount of money that needs to be payed from all of the clients
	double totalInterest = 0;							 // the amount of interest in dollars that accumulated from all of the clients

	fin.open(inFileName);
	if (fin.fail())
	{
		cout << "\nError opening " << inFileName << " for reading.\n";
		return EXIT_FAILURE;
	}

	fout.open(outFileName);
	if (fout.fail())
	{
		cout << "\nError opening " << outFileName << " for writing.\n";
		return EXIT_FAILURE;
	}

	displayHeadingReport(fout);
	readRecordLine(fin, name, loanType, APR, numberOfYears, PaymentPeriod, loanAmount);

	while (!fin.eof())
	{
		recordCount++;
		personalFinance = payment(APR, numberOfYears, PaymentPeriod, loanAmount);
		personalPayments = personalFinance * numberOfYears * PaymentPeriod;
		personalInterest = personalPayments - loanAmount;
		totalFinance += loanAmount;
		totalPayments += personalPayments;
		totalInterest += personalInterest;
		displayRecordLine(fout, name, loanType, loanAmount, numberOfYears, PaymentPeriod, APR, personalFinance, personalPayments, personalInterest);
		readRecordLine(fin, name, loanType, APR, numberOfYears, PaymentPeriod, loanAmount);
		
	}

	displayTotalValues(fout, recordCount, totalFinance, totalPayments, totalInterest);
	fout.close();
	fin.close();
	cout << "Processed " << recordCount << " records" << endl;
	cout << "Open " << outFileName << " to view report" << endl;
	
	return 0;
}

// Writes the headings onto output file
void displayHeadingReport(ostream& out)
{
	string title = "LOAN PAYMENT REPORT"; // Title of the report
	int titleLength = title.length();	  // Length of the title 
	string date = "October 2021";		  // Date the report was made
	int dateLength = date.length();       // length of the date
	int recordLineLength = TOTAL$ + $ + TOTAL_FIN + TOTAL_PAY + TOTAL_INT + 2;
	
	out << setw((recordLineLength - titleLength) / 2 + titleLength)
		<< title << endl;
	out << setw((recordLineLength - dateLength) / 2 + dateLength) 
		<< date << "\n\n";

	out << left << setw(WORDS) << "Name of" << setw(WORDS) << "Loan"
		<< right << setw(LOAN) << "Amount"
		<< setw(YEARS) << "Payment"
		<< setw(TERMS) << "Terms"
		<< setw(INTEREST) << "   "
		<< setw(MONEY_WORDS) << "Payment"
		<< setw(PAYMENT_WORD) << "Total"
		<< setw(MONEY_WORDS) << "Total" << endl;
	out << left << setw(WORDS) << "Borrower" << setw(WORDS) << "Type"
		<< right << setw(LOAN) << "Financed"
		<< setw(YEARS) << "Years"
		<< setw(TERMS) << "Per"
		<< setw(INTEREST) << "APR"
		<< setw(MONEY_WORDS) << "Amount"
		<< setw(PAYMENT_WORD) << "Payments"
		<< setw(MONEY_WORDS) << "Interest" << endl;
	for (int i = 1; i <= recordLineLength; i++) 
		out << "-";
	out << endl;
}

// Reads the current line of an input file
void readRecordLine(ifstream& fin, string& borrowerName, string& loanType, double& intRate, double& financedYears, int& paymentPeriod, double& loan)
{
	getline(fin, borrowerName, '\t');
	getline(fin, loanType, '\t');
	fin >> loan >> financedYears >> paymentPeriod >> intRate;
	fin.ignore(100, '\n');
	
}

// Writes the information from the input file onto an output file
void displayRecordLine(ostream& out, string borrowerName, string loanType, double loan, double financedYears, int paymentPeriod, double intRate, double perFin, double perPay, double perInt)
{
	static int recordCount; // keeps count of the amount of records in the file 

	recordCount++;
	out << left << setw(WORDS) << borrowerName 
		<< setw(WORDS) << loanType
		<< fixed << setprecision(2) << right
		<< setw(DOLLAR) << (recordCount == 1 ? '$' : ' ')
		<< setw(MONEY) << loan
		<< setprecision(1) << setw(YEARS) << financedYears 
		<< setw(TERMS) << paymentPeriod
		<< setprecision(2) << setw(YEARS) << intRate << "%"
		<< setw(DOLLAR) << (recordCount == 1 ? '$' : ' ')
		<< setw(MONEY) << perFin
		<< setw(DOLLAR) << (recordCount == 1 ? '$' : ' ')
		<< setw(PAYMENT) << perPay
		<< setw(DOLLAR) << (recordCount == 1 ? '$' : ' ')
		<< setw(MONEY) << perInt << endl;
}

// Writes the amounts of monthly payments, payments, and interest from all accounts onto an output file 
void displayTotalValues(ostream& out, int recordCount, double totalFinance, double totalPayments, double totalInterest)
{
	int recordLineLength = TOTAL$ + $ + TOTAL_FIN + TOTAL_PAY + TOTAL_INT + 2;

	for (int i = 1; i <= recordLineLength; i++)
		out << "-";
	out << endl;

	out << setw(TOTAL$) << "Totals   $" 
		<< setw(TOTAL_FIN) << totalFinance 
		<< setw($) << "$" << setw(TOTAL_PAY) << totalPayments << " $" 
		<< setw(TOTAL_INT) << totalInterest << endl
	    << setw(TOTAL$) << "Average   $" 
		<< setw(TOTAL_FIN) << average(totalFinance, recordCount)
	    << setw($) << "$" << setw(TOTAL_PAY) << average(totalPayments, recordCount) << " $" 
		<< setw(TOTAL_INT) << average(totalInterest, recordCount) << endl;
}

