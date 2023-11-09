#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(string inputString);
bool isMatch(char openSymbol, char closedSymbol);

int main()
{
	ifstream fin;
	string helloWorld;
	int counter = 1;

	fin.open("HelloWorld.txt");
	if (fin.fail())
	{
		cout << "File not found!" << endl;
		return -1;
	}

	while (!fin.eof())
	{
		getline(fin, helloWorld, '\n');
		cout << boolalpha << counter << ": " << isBalanced(helloWorld) << endl;
		counter++;
	}
	fin.close();


	return 0;
}

bool isBalanced(string inputString)
{
	stack<char> openSymbolStack;

	for (auto& currentChar : inputString)
	{
		if (currentChar == '(' || currentChar == '{')
		{
			openSymbolStack.push(currentChar);
		}
		if (currentChar == ')' || currentChar == '}')
		{
			if (isMatch(openSymbolStack.top(), currentChar))
			{
				openSymbolStack.pop();
			}
			else
			{
				return false;
			}
		}
	}
	if (!openSymbolStack.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool isMatch(char openSymbol, char closedSymbol)
{
	if (openSymbol == '(' && closedSymbol == ')')
	{
		return true;
	}
	else if (openSymbol == '{' && closedSymbol == '}')
	{
		return true;
	}
	else
	{
		return false;
	}
}
