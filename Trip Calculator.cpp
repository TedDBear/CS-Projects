// Stephen Craig
// COSC 1436 Pa1 - Trip Estimator
// Created 8/25/2021
// program computes and outputs the amount of gas needed, and the cost of a trip
#include <iostream>
#include <iomanip>
using namespace std;

const int SENTINEL = 0;

int main()
{
	int tripDistance;		// distance of the trip in miles
	double milesPerGal;		// miles per gallon estimate of the car 
	double avgGasCost;		// average cost of a gallon of gas in US dollars
	double gasNeeded;		// total number of gallons of gas needed
	double costOfTrip;		// estimated cost of the trip in US dollars

	cout << "Trip Estimator\n\n";
	cout << "What is the trip distance? ";
	cin >> tripDistance;
	while (tripDistance != SENTINEL)
	{

		cout << "\n\nHow many MPG does the car go? ";
		cin >> milesPerGal;

		cout << "\n\nHow much does a gallon of gas cost in your area? ";
		cin >> avgGasCost;

		gasNeeded = tripDistance / milesPerGal;
		costOfTrip = gasNeeded * avgGasCost;

		cout << "\nTrip Distance: " << tripDistance << endl;
		cout << "Miles Per Gallon: " << milesPerGal << endl;
		cout << "Average Gas Cost: " << avgGasCost << endl;
		cout << fixed << setprecision(1);
		cout << "\nThe amount of gas needed: " << gasNeeded << endl;
		cout << "The Cost of the Trip: " << costOfTrip << endl; 

		cout << "\nWhat is the trip distance? ";
		cin >> tripDistance;
	}
	cout << "\nThank You for using the Trip Estimator\n GOODBYE!";

		return 0;
}
