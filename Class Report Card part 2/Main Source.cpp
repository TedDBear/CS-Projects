// Stephen Craig
// COSC 1436 Pa8 - Grade Report using Arrays
// created 10/25/2021
// program displays the student's min, max, average, and grade letter
#include "myLibrarySC.h"
#include "SearchAndSortTemplate.cpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>

using namespace std;

const int WORDS = 25, GRADES = 10, NUMB_GRADES = 10;
void readGradeData(string name[], int report[][NUMB_GRADES], const int classSize, int& recordCount, string& inputFile);
void displayMenu();
void displayReportHeading(string inputFile, ostream& out);
void readStudentRecord(fstream& fin, string& student, int list[], const int size);
void displayStudentRecord(string name, const int list[], const int size);
void displayGradeReport(ostream& out, string inputFile, const string names[], const int minimum[], const int maximum[], const double average[], const char gradeLetter[], const int recordSize);

int main()
 {
	const int CLASS_SIZE = 20;					// the maximum number of students that a class can have 
	string name;								// the name of the student
	int recordCount = 0;						// the number of records read
	int fileCount = 0;							// the number of files read
	int menuSelect;								// the number to input to choose from a menu
	char userAnswer;							// a letter to store a user's answer
	int gradesAry[CLASS_SIZE][NUMB_GRADES];		// the two dimensional array to store grades
	string studentAry[CLASS_SIZE];				// the array to store student's names
	int minAry[CLASS_SIZE];						// the array to store the minimum values
	int maxAry[CLASS_SIZE];						// the array to store the maximum values
	double averageAry[CLASS_SIZE];				// the array to store the students' average
	char letterGradeAry[CLASS_SIZE];			// the array to store the letter grades
	string inFileName;							// the name of the input file
	string outFileName;							// the name of the output file
	string::size_type pos;						// the position of the ".txt" extension on an output file
	fstream fin;								// input file stream
	fstream fout;								// output file stream

	do
	{
		recordCount = 0;
		readGradeData(studentAry, gradesAry, CLASS_SIZE, recordCount, inFileName);
		for (int i = 0; i < recordCount; i++)
		{
			minAry[i] = min(gradesAry[i], NUMB_GRADES);
			maxAry[i] = max(gradesAry[i], NUMB_GRADES);
			averageAry[i] = round(average(gradesAry[i], NUMB_GRADES));
			letterGradeAry[i] = grade(averageAry[i]);
		}

		do
		{
			displayMenu();
			menuSelect = readInt("Menu Choice", 1, 5);
			// holdAndClearScreen("Press Enter to continue");
			switch (menuSelect)
			{
			case 1: selSort(studentAry, minAry, maxAry, averageAry, letterGradeAry, recordCount);    
					break; 
			case 2: selSort(minAry, studentAry, maxAry, averageAry, letterGradeAry, recordCount);    
					break; 
			case 3: selSort(maxAry, minAry, studentAry, averageAry, letterGradeAry, recordCount);
					break;
			case 4: selSort(averageAry, minAry, maxAry, studentAry, letterGradeAry, recordCount);
					break;
			case 5: selSort(letterGradeAry, minAry, maxAry, averageAry, studentAry, recordCount);
					break;
			default: cout << "Error";
			}
			system("cls");
			displayGradeReport(cout, inFileName, studentAry, minAry, maxAry, averageAry, letterGradeAry, recordCount);
			cout << "\nDo you want to save this report? (Y/N) ";
			userAnswer = readChar("Answer");
			if (userAnswer == 'Y')
			{
				if (!fout.is_open())
				{
					outFileName = inFileName;
					pos = outFileName.find(".txt");

					if (pos == string::npos)
						outFileName.append(" Grade Report.txt");
					else
						outFileName.insert(pos, " Grade Report");

					openIOFile(fout, outFileName, ios::out | ios::app);
				}
				displayGradeReport(fout, inFileName, studentAry, minAry, maxAry, averageAry, letterGradeAry, recordCount);
			}
			
			cout << "\nDo you want to change the sort order? (Y/N) ";
			userAnswer = readChar("Answer");
			system("cls");
		} while (userAnswer == 'Y');

		fout.close();

	} while (true);

	
	

	return 0;
}

void readGradeData(string name[], int report[][NUMB_GRADES], const int classSize, int& recordCount, string& inputFile)
{
	string studentName;
	fstream fin;
	const string QUIT = "Q";

	cout << "What is the name of the file? (or press "<< QUIT << " to quit) ";
	getline(cin, inputFile);

	if (inputFile.length() > 0)
	{
		inputFile[0] = toupper(inputFile.at(0));
	}

	if (inputFile == QUIT)
	{
		cout << "Thank you for using Ted D Bear's Grade Reporter " << endl;
		system("pause");
		exit(EXIT_SUCCESS);
	}
	
	openIOFile(fin, inputFile, ios::in);

	getline(fin, studentName, '\t');    
	
	while (recordCount < classSize && !fin.eof())
	{
		name[recordCount] = studentName;
		
		for (int i = 0; i < NUMB_GRADES; i++)
		{
			fin >> report[recordCount][i];
		}

		fin.ignore(100, '\n');
		getline(fin, studentName, '\t');
		recordCount++;
	}
	if (!fin.eof())
		cout <<	"\n\nError! The class size is not correct because there are more records remaining in file \n\n\n";
	fin.close();	
}

void displayMenu()
{
	// holdAndClearScreen("Press enter to continue");

	cout << "Pick a number between 1 and 5 to tell us how would you like to sort your report?\n\n";
	cout << "\t1. Student Name\n"
			"\t2. Minimum Grade\n"
			"\t3. Maximum Grade\n"
			"\t4. Average Grade\n"
			"\t5. Letter Grade\n"
			"Your Menu Choice? ";
}

// displays the heading onto the monitor
void displayReportHeading(string inputFile, ostream& out)
{
	string::size_type pos;
	string title;
	string::size_type titleLength;
	double recordLine = WORDS + GRADES * 4;
	double centerTitle;
	
	pos = inputFile.find(".txt");

	if (pos != string::npos)
		inputFile.erase(pos);

	title = "Grade Report for " + inputFile + " - " + getDate("%B %#d, %Y");
	titleLength = title.length();
	centerTitle = (recordLine - titleLength) / 2 + titleLength;

	out << endl << setw(centerTitle) << title << "\n\n";

	out << left << setw(WORDS) << "Student Name"
		<< right << setw(GRADES) << "Min"
		<< setw(GRADES) << "Max"
		<< setw(GRADES) << "Average"
		<< setw(GRADES) << "Grade" << endl;
	
	for (int i = 1; i <= recordLine; i++)
		out << "-";
	out << endl;


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



void displayGradeReport(ostream& out, string inputFile, const string names[], const int minimum[], const int maximum[], const double average[], const char gradeLetter[], const int recordSize)
{

	displayReportHeading(inputFile, out);
	for (int i = 0; i < recordSize; i++)
	{
		string student = names[i];
		student = reverseName(student);
		out << left << setw(WORDS) << student
			<< right << setw(GRADES) << minimum[i]
			<< setw(GRADES) << maximum[i]
			<< setw(GRADES) << fixed << setprecision(1) << average[i]
			<< setw(GRADES) << gradeLetter[i] << endl;
	}
	
}





