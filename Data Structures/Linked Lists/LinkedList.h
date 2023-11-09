#pragma once
#include <iostream>
#include <forward_list>
using namespace std;

template <typename T>
struct Node
{
	T data;
	Node <T> *link;
};

template <typename T>
class LinkedList
{
private:
	int nodeCounter;
	Node <T> *first;
	Node <T> *last;
public:
	void print()
	{
		Node <T>* current;
		current = first;

		while (current != NULL)
		{
			cout << current->data << endl;
			current = current->link;
		}
	}

	void swap(Node<T> *data1, Node <T> *data2)
	{
		T temp = data1->data;
		data1->data = data2->data;
		data2->data = temp;
	}

	void merge(LinkedList& list1, LinkedList list2)
	{ 
		list1.last->link = list2.first;
		nodeCounter = list1.nodeCounter + list2.nodeCounter;
	}

	int length()
	{
		return nodeCounter;
	}

	void insertFirst(const T& newInfo)
	{
		Node<T> *newNode = new Node<T>;
		newNode->data = newInfo;
		newNode->link = first;
		first = newNode;
		
		if (last == NULL)
		{
			last = newNode;
		}

		nodeCounter++;
	}

	void insertAfter(Node<T> *previous, T insertedValue)
	{
		Node<T> *newNode = new Node<T>;
		newNode->data = insertedValue;
		newNode->link = previous->link;
		previous->link = newNode;
		nodeCounter++;
	}

	Node<T>* getNode(int nodePosition)
	{
		Node<T>* current = new Node<T>;
		current = first;

		for (int i = 0; i < nodePosition; i++)
		{
			current = current->link;
		}

		return current;
	}

	int getNodeCounter()
	{
		return nodeCounter;
	}

	bool search(const T& valueToFind)
	{
		Node<T>* current = first;
		bool found = false;

		while (current != NULL && !found)
		{
			if (current->data == valueToFind)
			{
				found = true;
			}
			else
			{
				current = current->link;
			}
			
		}
		return found;
	}

	void deleteNodeWithData(T dataToDelete)
	{
		Node<T> *current;
		Node<T> *temp;
		bool found = false;

		if (first->data == dataToDelete)
		{
			found = true;
			current = first;
			first = first->link;
			delete current;
			nodeCounter--;
		}
		else
		{
			found = false;
			temp = first;
			current = first->link;

			while (current != NULL and !found)
			{
				if (current->data != dataToDelete)
				{
					temp = current;
					current = current->link;
				}
				else
				{
					found = true;
				}
			}
			if (found)
			{
				temp->link = current->link;

				if (last == current)
				{
					last = temp;
				}

				delete current;
				nodeCounter--;
			}
			else
			{
				cout << "Data " << dataToDelete << " not found!" << endl;
			}
		}
	}

	LinkedList()
	{
		nodeCounter = 0;
		first = NULL;
		last = NULL;
	}
};