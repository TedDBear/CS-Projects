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

// prompts user to input a number between -DBL_MAX and DBL_MAX
double readDouble(string InputStr = "Entry", double min = -DBL_MAX, double max = DBL_MAX);

// the amount that needs to be payed
double payment(double annIntRate, double finYear, int payPerYear, double loan); 

// rounds the number a certain number of places
double round(double number, int numDigit);

#endif


