#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <filesystem>
#include "Tokenizer.h"
//#include "Tokenizer.cpp"


using namespace std;
namespace fs = filesystem;

void readFiles(Tokenizer);
void writeToFile();
void compareDocuments();
bool binarySearch(vector<string>, string);

vector<vector<string>> documentTerms;

vector <pair<string, vector<string>>> documentCollection;
int main()
{
    Tokenizer document;
    
    readFiles(document);
    writeToFile();
    compareDocuments();
   
    return 0;
}

void readFiles(Tokenizer document)
{
    pair<string, vector<string>> documentData;

    //Tokenize all of the flies under the research paper folder.
    for (auto& p : fs::directory_iterator{ "./Research Papers" })
    { 
        ifstream file{ p.path() };

        string fileName = p.path().filename().string();

        if (file.fail())
        {
            cout << "File could not be opened" << endl;
            EXIT_FAILURE;
        }

        string line;// extracts each page of the file
        ofstream sentence("sentence.txt");// stores the terms after a temple phrase

        while (!file.eof())
        {
            getline(file, line);
            int pos = 0;
           
            string templateWord;// A temple word or phrase 
            ifstream templateFile("Template Words.txt");//

            while (!templateFile.eof())
            {
                getline(templateFile, templateWord);
                int pos = 0;
                while (pos != -1)
                {
                    if (line.find(templateWord) == string::npos)
                    {
                        pos = -1;
                    }
                    else
                    {
                        pos = line.find(templateWord, pos + templateWord.length());
                    }



                    if (pos != -1) // WILL SEARCH for "in this paper" in file
                    {
                        for (size_t i = pos + templateWord.length(); line.at(i - 1) != '.'; i++)
                        {
                            if (i == line.length())
                            {
                                getline(file, line);
                                i = 0;
                                sentence << " " << line[i];
                            }
                            else
                            {
                                sentence << line[i];
                            }
                        }
                    }
                }
            }
        }

        file.close();

        sentence.close();
        ifstream documentTokens("sentence.txt");

        vector<string> terms = document.tokenizer(documentTokens);
        
        documentData.first = fileName;
        documentData.second = terms;
        documentCollection.push_back(documentData);
        terms.clear();
        sentence.clear();

    }


}

void writeToFile() {
    ofstream fout("document terms list.txt"); //creates a list of the terms for each document to reference after calculations.


    for (int i = 0; i < documentCollection.size(); i++)
    {
        fout << documentCollection[i].first << endl;
        vector<string> terms = documentCollection[i].second;
        for (int j = 0; j < terms.size(); j++)
        {
            fout << terms[j] << endl;
        }
        fout << endl;
    }

}

void compareDocuments()
{
    string compareTerm;
    string comparedDocuments;
    bool hasSameTerm;
    double sharedTerms = 0.0;
    int totalTermsCompared = 0;
    double weightedScore = 0.0;
    pair<string, double> twoDocumentsScore;
    vector<pair<string, double>> comparedDocumentsScores; //Stores all of the compared documents with a weighted score greater than 0.


    cout << "Comparing Documents" << endl;
    for (int i = 0; i < documentCollection.size(); i++)
    {
        string document1Name = documentCollection[i].first;
        vector<string> document1 = documentCollection[i].second;
        for (int j = 1; j < documentCollection.size(); j++)
        {
            string document2Name = documentCollection[j].first;
            vector<string> document2 = documentCollection[j].second;
            if (j > i)
            {
                for (int k = 0; k < document1.size(); k++)
                {
                    compareTerm = document1[k];
                    hasSameTerm = binarySearch(document2, compareTerm);
                    if (hasSameTerm)
                    {
                        sharedTerms++;
                    }
                }
                comparedDocuments = document1Name + " and " + document2Name;
                totalTermsCompared = document1.size() + document2.size();
                weightedScore = sharedTerms / totalTermsCompared;

                if (weightedScore > 0.0)
                {
                    twoDocumentsScore.first = comparedDocuments;
                    twoDocumentsScore.second = weightedScore;
                    comparedDocumentsScores.push_back(twoDocumentsScore);
                }

                totalTermsCompared = 0;
                sharedTerms = 0;
            }
        }
    }

    sort(comparedDocumentsScores.begin(), comparedDocumentsScores.end(), [](auto& left, auto& right)
        {
            return left.second > right.second;
        });

    for (int i = 0; i < comparedDocumentsScores.size(); i++)
    {
        cout << "\n" << comparedDocumentsScores[i].first << endl;
        cout << "Weighted Score: " << setprecision(3) << comparedDocumentsScores[i].second << endl;
    }
}

bool binarySearch(vector<string> doc, string searchValue)
{
    bool found = false;
    int first = 0;
    int last = doc.size() - 1;
    int middle = 1;

    while (first <= last && !found)
    {
        middle = (first + last) / 2;

        if (doc[middle] == searchValue)
        {
            found = true;
        }

        else if (doc[middle] > searchValue)
        {
            last = middle - 1;
        }

        else
        {
            first = middle + 1;
        }

    }
    return found;
}

