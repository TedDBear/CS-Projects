#include "Tokenizer.h"
//#include "porter2_stemmer.cpp"
void Tokenizer::readFiles()
{
	ifstream file;
	string fileType = ".txt";
	vector<string> newTerms; //Stores the current document's terms.

	//Change 32 to the number of documents in a folder.
	for (int i = 1; i <= 32; i++)
	{
		string filename = to_string(i) + fileType;
		file.open(filename);
		ifstream& readFile = file;
		newTerms = tokenizer(readFile);
		file.close();
		documentTerms.push_back(newTerms);
	}
}

vector<string> Tokenizer::tokenizer(ifstream& file)
{
	string token;
	vector<string> terms;

	while (file >> token)
	{
		//Makes all of the letters lowercase
		for (auto& i : token)
		{
			i = tolower(i);
		}

		stemmer(token);

		tokens.push_back(token);
	}

	for (int i = 0; i < tokens.size(); i++)
	{
		token = tokens.at(i);

		bool stopWord = stopList(token);

		if (!stopWord && token != "")
		{
			//Increases term count by 1
			termCount++;
			//Adds the tokens to the last position.
			terms.push_back(token);

			// "terms.size() - 1" checks all of the tokenss inside except for the tokens pushed
			for (int i = 0; i < terms.size() - 1; i++)
			{
				if (terms.at(i) == token)
				{
					//Removes the last tokens pushed if it is already in the vector.
					terms.pop_back();
				}

			}
			
			//Sorts terms in alpbabetical order.
			sort(terms.begin(), terms.end());

			//performs the same operation as before, but for the total terms vector

			totalTerms.push_back(token);
			for (int i = 0; i < totalTerms.size() - 1; i++)
			{
				if (totalTerms.at(i) == token)
				{
					//Removes the last tokens pushed if it is already in the vector.
					totalTerms.pop_back();
				}

			}
		}
	}
	sort(totalTerms.begin(), totalTerms.end());
	tokens.clear();

	return terms;
}

void Tokenizer::stemmer(string& word)
{
	if (word.find("\\n") != string::npos)
	{
		word.erase(word.find("\\n"), 2);
	}
	removePunctuation(word);

	//Calls the removeSuffixes function if the word's length is greater than 4.
	if (word.length() > 4)
	{
		Porter2Stemmer::trim(word);
		Porter2Stemmer::stem(word);
	}
	
}

void Tokenizer::removeSuffixes(string& word)
{
	//Stores the length of the tokens.
	size_t len = word.length();

	//Removes the suffixes of tokens ending in -s, -er, -ed, -ing, -est, -ment, and -tion.
	if (word.at(len - 1) == 's')
	{
		//Checks to see if the tokens's length will still be greater than or equal to 4 if the suffix is removed.
		if (len - 1 >= 4)
		{
			word.pop_back();
		}
	}
	else if (word.substr((word.length() - 2), 2) == "er"
			 || word.substr((word.length() - 2), 2) == "ed")
	{
		if (len - 2 >= 4)
		{
			word.erase(len - 2, 2);
		}
	}
	else if (word.substr((word.length() - 3), 3) == "ing"
			 || word.substr((word.length() - 3), 3) == "est")
	{
		if (len - 3 >= 4)
		{
			word.erase(len - 3, 3);
		}

	}
	else if (word.substr((word.length() - 4), 4) == "ment"
			 || word.substr((word.length() - 4), 4) == "tion")
	{
		if (len - 4 >= 4)
		{
			word.erase(len - 4, 4);
		}
	}

}

void Tokenizer::removePunctuation(string& word)
{
	size_t len = word.length();
	for (int i = 0; i < len; i++)
	{
		if (ispunct(word[i]))
		{
			if (word[i] == '-')
			{
				removeHyphens(word);
				len = word.length();
				i = 0;
			}
			else while(ispunct(word[i]))
			{
				word.erase(i, 1);
				len = word.length();
			}
		}
	}
	

}

void Tokenizer::removeHyphens(string& word)
{
	string fragmentOfWord; //Stores the word before the hyphen.
	size_t len = word.length();
	for (int i = 0; i < len; i++)
	{
		if (word[i] == '-')
		{
			fragmentOfWord = word.substr(0, i);
			tokens.push_back(fragmentOfWord);
			word.erase(0, i + 1);
			len = word.length();
			break;
		}
	}
	
}

bool Tokenizer::stopList(string word)
{
	string bannedWord;
	ifstream stopList;
	stopList.open("Stop List.txt");

	while (stopList >> bannedWord)
	{
		if (word == bannedWord)
			return true;
	}
	
	return false;
}

void Tokenizer::booleanIncidenceMatrix()
{
	size_t termLen = totalTerms.size();
	size_t len = documentTerms.size();
	ofstream matrix;
	matrix.open("BooleanIncidenceMatrix.csv");

	matrix << "Terms,";
	for (int i = 0; i < len; i++)
	{
		matrix << i + 1 << ".txt,";
	}
	matrix << endl;

	for (int h = 0; h < termLen; h++)
	{
		string findTerm = totalTerms[h];
		matrix << right << findTerm << ",";
		for (int i = 0; i < len; i++)
		{
			bool inDoc = binarySearch(documentTerms[i], findTerm);
			matrix << inDoc << ",";
		}
		matrix << endl;
	}
}

bool Tokenizer::binarySearch(vector<string> doc, string searchValue)
{
	bool found = false;
	int first = 0;
	int last = doc.size() - 1;
	int middle;

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
	if (found)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<string> Tokenizer::biWordIndex(vector<string> terms)
{
	vector<string> biWords;
	string biTerm;
	for (int i = 0; i + 1 < terms.size(); i++)
	{
		biTerm = terms[i] + " " + terms[i + 1];

		biWords.push_back(biTerm);

		for (int i = 0; i < biWords.size() - 1; i++)
		{
			if (biWords[i] == biTerm)
			{
				biWords.pop_back();
			}

		}
		sort(biWords.begin(), biWords.end());
		totalBiWordTerms.push_back(biTerm);

		for (int i = 0; i < totalBiWordTerms.size() - 1; i++)
		{
			if (totalBiWordTerms[i] == biTerm)
			{
				//Removes the last tokens pushed if it is already in the vector.
				totalBiWordTerms.pop_back();
			}

		}
	}
	sort(totalBiWordTerms.begin(), totalBiWordTerms.end());

	return biWords;
}

void Tokenizer::setTermCount(int termCount)
{
	this->termCount = termCount;
}

int Tokenizer::getTermCount()
{
	return termCount;
}

void Tokenizer::setDocumentTerms(vector<string> document)
{
	documentTerms.push_back(document);
}

vector<vector<string>> Tokenizer::getDocumentTerms()
{
	return documentTerms;
}

vector<string> Tokenizer::getTotalTerms()
{
	return totalTerms;
}

vector<string> Tokenizer::getTotalBiWordTerms()
{
	return totalBiWordTerms;
}

void Tokenizer::setDocumentTermCount(string document, int totalTerms)
{
	documentTermCount[document] = totalTerms;
}

map<string, int> Tokenizer::getDocumentTermCount()
{
	return documentTermCount;
}

void Tokenizer::setTermFrequency()
{
	string term;
	int frequency = 0;
	string fileType = ".txt";
	string word;
	for (int i = 0; i < totalTerms.size(); i++)
	{
		term = totalTerms[i];
		for (int j = 1; j <= 32; j++)
		{
			string filename = to_string(j) + fileType;
			ifstream file(filename);
			while (!file.eof())
			{
				file >> word;
				for (auto& i : word)
				{
					i = tolower(i);
				}
				if (word.find('-') != string::npos)
				{
					while (word.find('-') != string::npos)
					{
						int pos = word.find('-');
						string fragmentOfWord = word.substr(0, pos);
						word.erase(0, pos + 1);
						if (term == fragmentOfWord)
						{
							frequency++;
						}
					}
				}
				else
				{
					removePunctuation(word);
					if (term == word)
					{
						frequency++;
					}
				}
			}
			if (frequency > 0)
			{
				string docID;
				if (j < 10)
				{
					docID = "0" + to_string(j);
				}
				else 
				{
					docID = to_string(j);
				}
				termFrequency[term].insert(make_pair(docID, frequency));
				frequency = 0;
			}
			
		}
		

	}
	
	
}

map<string, map<string, int>> Tokenizer::getTermFrequency()
{
	return termFrequency;
}

void Tokenizer::setDocumentFrequency()
{
	string term;
	int frequency = 0;
	for (int i = 0; i < totalTerms.size(); i++)
	{
		term = totalTerms[i];
		for (int j = 0; j < documentTerms.size(); j++)
		{
			for(int k =0; k < documentTerms[j].size(); k++)
			{
				if (term == documentTerms[j][k])
				{
					frequency++;
				}
			}
			documentFrequency[term] = frequency;
		}
		frequency = 0;
	}
}

map<string, int> Tokenizer::getDocumentFrequency()
{
	return documentFrequency;
}

map<string, double> Tokenizer::termFrequencyInverseDocumentFrequency(string query)
{
	double docInverse = 0.0;
	double score;
	map<string, double> TF_IDF;
	map<string, int>::iterator TF;
	double termFreq = 0;

	if (documentFrequency[query] == 0)
	{
		cout << "Error! \"" << query << "\" is an invalid term." << endl;
		TF_IDF[query] = 0;
		return TF_IDF;
	}
	
	docInverse = 1.0 / (documentFrequency[query]);

	for (TF = termFrequency[query].begin(); TF != termFrequency[query].end(); ++TF)
	{
		termFreq = static_cast<double>(TF->second) / documentTermCount[TF->first];
		score = docInverse * termFreq;
		TF_IDF[TF->first] = score;
		
	}
	
	return TF_IDF;
	
}

vector<pair<string, double>> Tokenizer::findTopFiveDocuments(vector<string> queryTerms)
{
	map<string, double> termTF_IDF;
	map<string, double>::iterator itr;
	vector<pair<string, double>> topFiveDocuments;
	string term;
	for (int i = 0; i < queryTerms.size(); i++)
	{
		term = queryTerms[i];
		termTF_IDF = termFrequencyInverseDocumentFrequency(term);


		TF_IDFScore[term] = termTF_IDF;
		
		
		termTF_IDF.clear();
	}

	for (auto& entry : TF_IDFScore)
	{

		for (auto& docScore : entry.second)
		{
			topFiveDocuments.push_back(docScore);
		}
	}

	for (int i = 0; i < topFiveDocuments.size() - 1; i++)
	{
		for (int j = 0; j < topFiveDocuments.size(); j++)
		{
			if (j > i)
			{
				if (topFiveDocuments[i].first == topFiveDocuments[j].first)
				{
					topFiveDocuments[i].second = topFiveDocuments[i].second + topFiveDocuments[j].second;
					topFiveDocuments.erase(next(topFiveDocuments.begin() + j - 1));
				}
			}
		}
	}

	sort(topFiveDocuments.begin(), topFiveDocuments.end(), [](auto& left, auto& right)
		{
			return left.second > right.second;
		});

	for (int i = topFiveDocuments.size(); i > 5; i--)
	{
		topFiveDocuments.pop_back();
	}

	return topFiveDocuments;
}

vector<pair<string, double>> Tokenizer::calculateZoneScores(string query)
{
	vector<pair<string, double>> zoneScores;
	map<string, double> documentScore;
	double score = 0.0;
	int lineCounter = 0;
	string line;
	map<string, int>::iterator itr;
	string filename;
	ifstream file;
	
	for (itr = termFrequency[query].begin(); itr != termFrequency[query].end(); ++itr)
	{
		bool foundAtLastZone = false;

		if (itr->first[0] == '0')
		{ 
			filename.append(1, itr->first[1]);
			filename += ".txt";
		}
		else
		{
			filename = itr->first + ".txt";
		}

		file.open(filename);

		while (!file.eof() && foundAtLastZone == false)
		{
			getline(file, line);

			for (auto& i : line)
			{
				i = tolower(i);
			}
			lineCounter++;

			switch (lineCounter)
			{
			case 1:
				if (line.find(" " + query + " ") != string::npos)
				{
					score += .4;
				}
				break;
			case 2:
				if (line.find(" " + query + " ") != string::npos)
				{
					score += .25;
				}
				break;
			case 3:
				if (line.find(" " + query + " ") != string::npos)
				{
					score += .15;
				}
				break;
			default:
				if (line.find(" " + query + " ") != string::npos)
				{
					score += .2;
					foundAtLastZone = true;
				}
			}
		}
		documentScore[itr->first] = score;
		lineCounter = 0;
		score = 0;
		file.close();
	}

	for (auto& docScore : documentScore)
	{
		zoneScores.push_back(docScore);
	}

	sort(zoneScores.begin(), zoneScores.end(), [](auto& left, auto& right)
		{
			return left.second > right.second;
		});

	return zoneScores;
}

void Tokenizer::invertedIndex()
{
	size_t termLen = totalTerms.size();
	size_t len = documentTerms.size();
	ofstream index;
	index.open("InvertedIndex.csv");

	index << "Terms,";
	index << endl;

	for (int h = 0; h < termLen; h++)
	{
		string findTerm = totalTerms[h];
		index << right << findTerm << ",";
		for (int i = 0; i < len; i++)
		{
			bool inDoc = binarySearch(documentTerms[i], findTerm);

			if (inDoc)
			{
				index << i + 1<< ",";
			}
		}
		index << endl;
	}
}

void Tokenizer::permutermIndex()
{
	ofstream index("permutermIndex.csv");
	string term;

	index << "Terms, " << endl;
	vector<string> permuterm;

	for (int i = 0; i < totalTerms.size(); i++)
	{
		term = totalTerms[i];
		//index << term + ",";
		for (int j = term.size(); j >= 0; j--)
		{
			permuterm.push_back(term.substr(term.size() - j, j) + "$" + term.substr(0, term.size() - j));
			//index << term.substr(term.size() - j, j) << "$" << term.substr(0, term.size() - j) << ",";
		}
		//index << endl;
		
	}
	sort(permuterm.begin(), permuterm.end());
	for (int j = 0; j < permuterm.size(); j++)
	{
		index << permuterm[j] << endl;
	}
	
	
}

