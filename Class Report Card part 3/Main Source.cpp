// Stephen Craig
// COSC 1436 PA9 - Grade Report using Enum and Struct
// created 11/8/2021
// program displays the students' grade using enums and structs and can search for a particular student within the file
#include "myLibrarySC.h"
#include "SearchAndSortTemplate.cpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;


const int WORDS = 25, WORD_GRADE = 9, COURSE_AVERAGE = 14, AVERAGE_GRADE = 9, GRADE_LETTER = 12, NUMB_GRADES = 10, CLASS_SIZE = 20, GRADE_DIST_SIZE = 6;
struct Student
{
	string studentName;
	int courseGrades[NUMB_GRADES];
	double courseAverage;
	GradeType letterGrade;
};
struct ClassStatistics
{
	string classID;
	int classCount = 0;
	double classAverage = 0;
	double highAverage = 0;
	double lowAverage = 0;
	int gradeDistribution[GRADE_DIST_SIZE] = { 0 };
};
void runGradeReport(Student roster[], ClassStatistics& stats);
void displayMenu();
void displayReportHeading(string inputFile, ostream& out);
bool compNameAsc(Student s1, Student s2);
bool compGradeAsc(Student s1, Student s2);
bool compAverageDesc(Student s1, Student s2);
double average(const Student list[], const int size);
double min(const Student list[], const int size);
double max(const Student list[], const int size);
void getGradeDistribution(const Student roster[], ClassStatistics& totalGrade);
void displayGradeReport(const Student grades[], const ClassStatistics& results);
void searchStudent(const Student roster[], const int studentCount);
void nameSearch(const Student list[], string item, const int length, int& index, bool& found);

int main()
 {
	Student roster[CLASS_SIZE];
	ClassStatistics stats;
	int choice;

	runGradeReport(roster, stats);
		do
		{
			displayMenu();

			choice = readInt("Menu Choice", 1, 5);

			switch (choice)
			{
			case 1: selSort(roster, stats.classCount, compNameAsc); break;
			case 2: selSort(roster, stats.classCount, compAverageDesc); break;
			case 3: selSort(roster, stats.classCount, compGradeAsc); break;
			case 4: selSort(roster, stats.classCount, compNameAsc); 
					searchStudent(roster, stats.classCount); break;
			case 5: break;
			}

			if (choice == 1 || choice == 2 || choice == 3)
			{
				system("cls");
				displayGradeReport(roster, stats);
				holdAndClearScreen("Press Enter to return to main menu.");
			}
		} while (choice != 5);

		cout << "Thank you for using Ted D Bear Production's Grade Reporter" << endl;
		system("pause");
		cout << "Good Bye";

	return 0;
}

void runGradeReport(Student roster[], ClassStatistics& stats)
{
	int recordCount = 0;
	string::size_type pos;
	string studentName;
	string fileName;
	ifstream fin;
	const string QUIT = "Q";

	cout << "What is the name of the file? (or press "<< QUIT << " to quit) ";
	getline(cin, fileName);

	if (fileName.length() > 0)
	{
		fileName[0] = toupper(fileName.at(0));
	}

	if (fileName == QUIT)
	{
		cout << "Thank you for using Ted D Bear's Grade Reporter " << endl;
		system("pause");
		cout << "\nGood Bye";
		exit(EXIT_SUCCESS);
	}
	
	fin.open(fileName);

	if (fin.fail())
	{
		cout << "Error opening " << fileName << " file for input.";
		system("pause");
		exit(EXIT_FAILURE);
	}


	getline(fin, studentName, '\t');    
	
	while (recordCount < CLASS_SIZE && !fin.eof())
	{
		roster[recordCount].studentName = studentName;
		
		for (int g = 0; g < NUMB_GRADES; g++)
		{
			fin >> roster[recordCount].courseGrades[g];
		}

		fin.ignore(100, '\n');
		getline(fin, studentName, '\t');
		recordCount++;
	}
	if (!fin.eof())
		holdAndClearScreen("Error! The class size is not correct because there are more records remaining in file");
	fin.close();

	pos = fileName.find(".txt");

	if (pos != string::npos)
		fileName.erase(pos);

	stats.classID = fileName;
	stats.classCount = recordCount;

	for (int i = 0; i < stats.classCount; i++)
	{
		roster[i].courseAverage = round(average(roster[i].courseGrades, NUMB_GRADES), 1);
		roster[i].letterGrade = getGrade(roster[i].courseAverage);
	}

	stats.classAverage = average(roster, stats.classCount);
	stats.lowAverage = min(roster, stats.classCount);
	stats.highAverage = max(roster, stats.classCount);
	getGradeDistribution(roster, stats);
	cout << endl;
}

void displayMenu()
{
	cout << "Please Select One of the Following Menu Options to Continue\n\n";
	cout << "\t1.   Ordered by Last Name (A to Z)\n"
			"\t2.   Ordered by Average (high to low)\n"
			"\t3.   Ordered by Grade (A to F)\n"
			"\t4. Search for Individual Student\n"
			"\t5. Exit Program\n\n"
			"Your Menu Choice? ";
}

// displays the heading onto the monitor
void displayReportHeading(string inputFile, ostream& out)
{
	string::size_type pos;
	string title;
	string date;
	string::size_type titleLength;
	string::size_type dateLength;
	string::size_type recordLine = WORDS + COURSE_AVERAGE + WORD_GRADE;
	string::size_type centerTitle;
	string::size_type centerDate;
	
	pos = inputFile.find(".txt");

	if (pos != string::npos)
		inputFile.erase(pos);

	title = "Grade Report for " + inputFile;
	transform(title.begin(), title.end(), title.begin(), ::toupper);
	titleLength = title.length();
	centerTitle = (recordLine - titleLength) / 2 + titleLength;

	date = getDate("%B, %Y");
	dateLength = date.length();
	centerDate = (recordLine - dateLength) / 2 + dateLength;

	out << endl << setw(centerTitle) << title << endl;
	out << setw(centerDate) << date << "\n\n";

	out << left << setw(WORDS) << "Student Name"
		<< right << setw(COURSE_AVERAGE) << "Course Average"
		<< setw(WORD_GRADE) << "Grade" << endl;
	
	for (int i = 1; i <= recordLine; i++)
		out << "-";
	out << endl;


}

// Compare Student structure studentName members for Ascending order
bool compNameAsc(Student s1, Student s2)
{
	return s1.studentName < s2.studentName;
}

//  Compare Student structure letterGrade members for Ascending order 
bool compGradeAsc(Student s1, Student s2)
{
	return s1.letterGrade > s2.letterGrade;
}

// Compare Student structure courseAverage members for Descending order 
bool compAverageDesc(Student s1, Student s2)
{
	return s1.courseAverage > s2.courseAverage;
}

double average(const Student list[], const int size)
{
	double realAverage = 0.0;

	if (size == 0)
		return 0;

	for (int i = 0; i < size; i++)
	{
		realAverage += list[i].courseAverage;
	}

	realAverage = average(realAverage, size);


	return realAverage;
}

double min(const Student list[], const int size)
{
	double min = INT_MAX;
	double grade;

	for (int i = 0; i < size; i++)
	{
		grade = list[i].courseAverage;

		if (grade < min)
			min = grade;

	}

	return min;
}

double max(const Student list[], const int size)
{
	double max = INT_MIN;
	double grade;

	for (int i = 0; i < size; i++)
	{
		grade = list[i].courseAverage;

		if (grade > max)
			max = grade;

	}

	return max;

}

void getGradeDistribution(const Student roster[], ClassStatistics& stats)
{
	for (int i = 0; i < stats.classCount; i++)
	{
		switch (roster[i].letterGrade)
		{
		case F: stats.gradeDistribution[F]++; break;
		case D: stats.gradeDistribution[D]++; break;
		case C: stats.gradeDistribution[C]++; break;
		case B: stats.gradeDistribution[B]++; break;
		case A: stats.gradeDistribution[A]++; break;
		case INVALID: stats.gradeDistribution[INVALID]++;
		}
	}
}

void displayGradeReport(const Student roster[], const ClassStatistics& stats)
{
	const int DIST1 = 12;
	const int DIST2 = 19;
	const int DIST3 = 12;
	const int DIST4 = 4;
	const int STATS = 7;

	displayReportHeading(stats.classID, cout);
	
	for (int i = 0; i < stats.classCount; i++)
	{
		cout << left << setw(WORDS) << reverseName(roster[i].studentName)
			 << right << setw(AVERAGE_GRADE) << fixed << setprecision(1) << roster[i].courseAverage
			 << setw(GRADE_LETTER) << gradeTypeToChar(roster[i].letterGrade) << endl;
	}

	cout << endl;
	cout << setw(DIST1) << " " << left << setw(DIST2) << "Number of Students:" << right << setw(STATS) << stats.classCount << endl
		 << setw(DIST1) << " " << left << setw(DIST2) << "Class Average:" << right << setw(STATS) << stats.classAverage << endl
		 << setw(DIST1) << " " << left << setw(DIST2) << "Highest Average" << right << setw(STATS) << stats.highAverage << endl
		 << setw(DIST1) << " " << left << setw(DIST2) << "Lowest Average:" << right << setw(STATS) << stats.lowAverage << endl << endl;


	for (GradeType i = A; i >= 1; i = GradeType(i - 1))
	{
		cout << left << setw(DIST1) << " " << setw(DIST3) << (i == A ? "NUMBER of: " : " ") << right << setw(DIST4)
			 << gradeTypeToChar(i) << "s " << setw(DIST4) << stats.gradeDistribution[i] << endl;
	}

	cout << left << setw(DIST1) << " " << setw(DIST3) << " " << right << setw(DIST4)
		 << gradeTypeToChar(INVALID) << "s " << setw(DIST4) << stats.gradeDistribution[INVALID] << endl;
}

void searchStudent(const Student roster[], const int studentCount)
{
	string name;
	bool found;
	int index;

	system("cls");

	do
	{
		cout << "Enter the Student's name \n(last, first middle) or press Q to quit searching: ";
		getline(cin, name);
		transform(name.begin(), name.end(), name.begin(), toupper);
		nameSearch(roster, name, studentCount, index, found);

		if (found)
		{
			cout << endl;
			cout << left << setw(WORDS) << reverseName(roster[index].studentName)
				<< right << setw(AVERAGE_GRADE) << roster[index].courseAverage
				<< setw(GRADE_LETTER) << gradeTypeToChar(roster[index].letterGrade) << endl;
			holdAndClearScreen("Press Enter to search again");
		}
		else if (name != "Q")
		{
			cout << "\nThe Name " << name << " is not found!\n";
			holdAndClearScreen("Press Enter to search again");
		}
	} while (name != "Q");
	system("cls");
}


void nameSearch(const Student list[], string item, const int length, int& index, bool& found)
{
	int i = 0;
	int search;
	string name;

	found = false;

	while (length > i && !found)
	{
		search = i++;

		name = list[search].studentName;

		transform(name.begin(), name.end(), name.begin(), toupper);

		if (item != name)
			found = false;
		else
			found = true;
	}
	if (found)
		index = search;
	else
		index = -1;
	}




