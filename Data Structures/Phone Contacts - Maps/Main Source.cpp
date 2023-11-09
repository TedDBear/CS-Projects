#include <iostream>
#include <map>

using namespace std;

struct PhoneRecord
{
	string name;
	string phoneNumber;
	string relationship;
	PhoneRecord()
	{
		name = "unknown";
		phoneNumber = "unknown";
		relationship = "unknown";
	}
	PhoneRecord(string name, string phoneNumber, string relationship)
	{
		this->name = name;
		this->phoneNumber = phoneNumber;
		this->relationship = relationship;
	}
	void printPhoneRecord()
	{
		cout << name << "\t" << phoneNumber << "\t" << relationship << endl;
	}
	friend ostream& operator << (ostream& osObj, const PhoneRecord& phoneRecObj);
};
ostream& operator << (ostream& osObj, const PhoneRecord& phoneRecObj)
{
	osObj << phoneRecObj.name << "\t" << phoneRecObj.phoneNumber 
		  << "\t" << phoneRecObj.relationship << endl;
	return osObj;
}


void addContact(map<string, PhoneRecord>& phoneMap) 
{
	string name;
	string phoneNum;
	string relationship;
	cout << "\nType in the name, phone number, and relationship of your new contact:" << endl;

	cin >> name;
	cin >> phoneNum;
	cin >> relationship;

	PhoneRecord newContact(name, phoneNum, relationship);
	phoneMap[name] = newContact;
}

void viewContact(const map<string, PhoneRecord>& phoneMap)
{
	string name;

	cout << "\nType in the name of the contact: ";
	cin >> name;

	if (phoneMap.find(name) != phoneMap.end())
	{
		cout << "\nContact information" << endl;
		cout << phoneMap.at(name) << endl;
	}
	else
	{
		cout << "Error! the name you entered does not match any of your contacts." << endl;
	}
}

void deleteContact(map<string, PhoneRecord>& phoneMap)
{
	string name;

	cout << "\nType in the name of the contact you want to delete: ";
	cin >> name;

	if (phoneMap.find(name) != phoneMap.end())
	{
		phoneMap.erase(name);
		cout << "Successfully deleted " << name << " from your contacts list" << endl;
	}
	else
	{
		cout << "Error! the name you entered does not match any of your contacts." << endl;
	}
}

void printAllContacts(const map<string, PhoneRecord>& phoneMap)
{
	cout << "\nContact list" << endl;
	for (auto pair : phoneMap)
	{
		cout << pair.second << endl;
	}
}

int main()
{
	map<string, PhoneRecord> phoneMap;
	int choice;

	do
	{
		cout << "What do you want to do with your phone contacts? " << endl;

		cout << "1. Add a new contact" << endl
			 << "2. View someone's information" << endl
			 << "3. Delete a contact" << endl
			 << "4. Print the entire list of contacts" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			cout << "Thank you for using this program. Have a good day!" << endl;
			break;
		case 1:
			addContact(phoneMap);
			break;
		case 2:
			viewContact(phoneMap);
			break;
		case 3:
			deleteContact(phoneMap);
			break;
		case 4:
			printAllContacts(phoneMap);
			break;
		default:
			cout << "Error! Your input must be between 0-4. Please try again." << endl;
		}
		system("pause");
		system("cls");
	} while (choice != 0);
	

	return 0;
}