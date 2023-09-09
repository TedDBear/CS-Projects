#include <iostream>
#include <vector>

using namespace std;

void typeCreditCard(vector<int>&);
void readCreditCard(vector<int>);
void dropSumDigit(vector<int>&, int&);
vector<int> reverseDigits(vector<int>);
void multiplyOddDigits(vector<int>&);
void subtractDigits(vector<int>&);
int sumOfDigits(vector<int>, int);

int main()
{
	
	vector<int> creditCardNumber;
	int testDigit = 0;
	int sum = 0;
	int remainderOfSum = 0;
	char answer = 'Y';

	cout << "Welcome to the Credit Card Validator" << endl;

	while (answer == 'Y' || answer == 'y')
	{
		cout << "Type in a credit card number: " << endl;
		typeCreditCard(creditCardNumber);

		cout << "Orignal CCN: " << endl;
		readCreditCard(creditCardNumber);

		dropSumDigit(creditCardNumber, testDigit);
		cout << "\nRightmost Digit: " << endl;
		cout << testDigit << endl;
		cout << "\nCCN after dropping the last digit: " << endl;
		readCreditCard(creditCardNumber);

		creditCardNumber = reverseDigits(creditCardNumber);
		cout << "\nCCN after reversing it: " << endl;
		readCreditCard(creditCardNumber);

		multiplyOddDigits(creditCardNumber);
		cout << "\nAfter Multiplying digits in the odd position by 2 (with spaces added): " << endl;
		for (int i = 0; i < creditCardNumber.size(); i++)
		{
			cout << creditCardNumber[i] << " ";
		}
		cout << endl;

		subtractDigits(creditCardNumber);
		cout << "\nAfter subtracting 9 from a digit if it is greater than 9: " << endl;
		readCreditCard(creditCardNumber);

		sum = sumOfDigits(creditCardNumber, sum);
		cout << "\nSum of Digits is: " << sum << endl;

		remainderOfSum = sum % 10;
		cout << "\nSum mod 10 is " << remainderOfSum << " and the rightmost digit is " << testDigit << endl;
		if (remainderOfSum == testDigit)
		{
			cout << "These are equal, So the CCN is valid." << endl;
		}
		else
		{
			cout << "These are not equal, So the CCN is not valid." << endl;
		}

		cout << "\nDo you want to read another credit card? (type 'y' to continue, or type any other character to exit) ";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			creditCardNumber.clear();
			system("cls");
		}
		else
		{
			cout << "\nThanks for using the credit card validator. Have a good day!" << endl;
		}
	}
	return 0;
}
void typeCreditCard(vector<int>& creditCardNumber)
{
	int number;
	for (int i = 0; i < 15; i++)
	{
		cout << "#" << i + 1 << " ";
		cin >> number;
		while (cin.fail() || number > 9 || number < 0)
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "INVALID NUMBER! please type a number between 0 and 9" << endl;
			cin >> number;
		}
		creditCardNumber.push_back(number);
		cout << endl;
	}
}

void readCreditCard(vector<int> ccn)
{
	for (int i = 0; i < ccn.size(); i++)
	{
		cout << ccn[i];
	}
	cout << endl;
}

void dropSumDigit(vector<int>& ccn, int& testDigit)
{
	testDigit = ccn[ccn.size() - 1];
	ccn.pop_back();
}

vector<int> reverseDigits(vector<int> ccn)
{
	size_t n = ccn.size() - 1;
	vector<int> reversedCCN(15);

	for (int i = 0; i < ccn.size(); i++)
	{
		reversedCCN[i] = ccn[n];
		n--;
	};
	return reversedCCN;
}

void multiplyOddDigits(vector<int>& ccn)
{
	for (int i = 0; i < ccn.size(); i++)
	{
		if (i % 2 == 0)
		{
			ccn[i] *= 2;
		}
	}
}

void subtractDigits(vector<int>& ccn)
{
	for (int i = 0; i < ccn.size(); i++)
	{
		if (ccn[i] > 9)
		{
			ccn[i] -= 9;
		}
	}
}

int sumOfDigits(vector<int> ccn, int sum)
{
	for (int i = 0; i < ccn.size(); i++)
	{
		sum += ccn[i];
	}

	return sum;
}
