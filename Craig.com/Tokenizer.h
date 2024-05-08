#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "porter2_stemmer.h"

using namespace std;
class Tokenizer
{
private:
	vector<string> totalTerms; //Stores all of the terms found.
	vector<string> tokens; //Stores tokens.
	vector<vector<string>> documentTerms; //Stores the terms of each document.
	vector<string> totalBiWordTerms; //Stores two words as one term.
	map<string, int> documentTermCount; //Stores the number of terms in a document.
	map<string, int> documentFrequency; //Stores a term's frequency in a document collection.
	map<string, map<string, int>> termFrequency; //Stores a term's frequency in a document.
	map<string, map<string, double>> TF_IDFScore; //Stores the term's TF-IDF score for each document.
	int termCount = 0; //Stores the number of terms in a document.
public:
	void readFiles(); //Reads all of the files.
	vector<string> tokenizer(ifstream&); //Turns the tokenss into terms and stores them in a vector. Important!, always call this function for each document.
	void stemmer(string&); 	//Trims the tokens down.
	void removeSuffixes(string&); //Removes the suffix from the tokens.
	void removePunctuation(string&); //Removes any punctuation.
	void removeHyphens(string&); //Removes hyphens.
	bool stopList(string); //Checks a list to see if a tokens is a stop word.
	void booleanIncidenceMatrix(); //Makes a boolean incidence matrix in excel.
	void invertedIndex(); //Makes an inverted index.
	void permutermIndex();//Makes a permuterm index.
	bool binarySearch(vector<string> doc, string searchValue);//Determines if a term was found in a document.
	vector<string> biWordIndex(vector<string>);
	void setTermCount(int);
	int getTermCount();
	void setDocumentTerms(vector<string>);
	vector<vector<string>> getDocumentTerms();
	vector<string> getTotalTerms();
	vector<string> getTotalBiWordTerms();
	void setDocumentTermCount(string, int);
	map<string, int> getDocumentTermCount();
	void setTermFrequency();
	map<string, map<string, int>> getTermFrequency();
	void setDocumentFrequency();
	map<string, int> getDocumentFrequency();
	map<string, double> termFrequencyInverseDocumentFrequency(string);//Calculates the TF-IDF Scores of each document that contains the query 
	vector<pair<string, double>> findTopFiveDocuments(vector<string>);//Finds the top 5 TF-IDF scores of each document. Use a vector containing all of the query terms.
	vector<pair<string, double>> calculateZoneScores(string);
};