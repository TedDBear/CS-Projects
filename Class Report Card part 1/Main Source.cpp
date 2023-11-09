// Stephen Craig
// COSC 1436 Pa7 - Grade Report using Arrays
// created 10/18/2021
// program displays the student's min, max, average, and grade letter
#include "myLibrarySC.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
using namespace std;

void displayReportHeading(string inputFile);
void readStudentRecord(fstream& fin, string& student, int list[], const int size);
void displayStudentRecord(string name, const int list[], const int size);
const int WORDS = 25, GRADES = 10;

int main()
{
	const int NUMB_GRADES = 10;					// the size the array will be
	string name;								// the name of the student
	int report[NUMB_GRADES];					// the array to store grades
	string inFileName = "COSC 1436 F21.txt";	// the name of the input file
	fstream fin;								// input file stream

	openIOFile(fin, inFileName, ios::in);
	displayReportHeading(inFileName);
	readStudentRecord(fin, name, report, NUMB_GRADES);
	
	while (!fin.eof())
	{
		
		displayStudentRecord(name, report, NUMB_GRADES);
		readStudentRecord(fin, name, report, NUMB_GRADES);
	}
	
	fin.close();

	return 0;
}

// displays the heading onto the monitor
void displayReportHeading(string inputFile)
{
	string::size_type pos;
	string title;
	string::size_type titleLength;
	double recordLine = WORDS + GRADES * 4;
	
	pos = inputFile.find(".txt");

	if (pos != string::npos)
		inputFile.erase(pos);

	title = "Grade Report for " + inputFile + " - " + getDate("%B %#d, %Y");
	titleLength = title.length();

	cout << setw((recordLine - titleLength) / 2 + titleLength)
		 << title << "\n\n";

	cout << left << setw(WORDS) << "Student Name"
		 << right << setw(GRADES) << "Min"
		 << setw(GRADES) << "Max"
		 << setw(GRADES) << "Average"
		 << setw(GRADES) << "Grade" << endl;
	
	for (int i = 1; i <= recordLine; i++)
		cout << "-";
	cout << endl;


}

// reads the student's record from the input file
void readStudentRecord(fstream& fin, string& student, int list[], const int size)
{
	getline(fin, student, '\t');

	for (int i = 0; i < size;)
	{
		fin >> list[i++];
	}

	fin.ignore(100, '\n');
}

// displays the student's record onto the monitor
void displayStudentRecord(string name, const int list[], const int size)
{
	int minimum;
	int maximum;
	double gradeAverage;
	char letterGrade;

	minimum = min(list, size);
	maximum = max(list, size);
	gradeAverage = round(average(list, size), 1);
	letterGrade = grade(gradeAverage);
	name = reverseName(name);
	cout << left << setw(WORDS) << name
		 << right << setw(GRADES) << minimum
		 << setw(GRADES) << maximum
		 << setw(GRADES) << fixed << setprecision(1) << gradeAverage
		 << setw(GRADES) << letterGrade << endl;
}





