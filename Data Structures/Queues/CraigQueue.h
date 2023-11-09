#pragma once
#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* link;
};

template<typename T>
class QueueADT
{
public:
	virtual bool isEmpty() = 0;
	virtual bool isFull() = 0;
	virtual T front() = 0;
	virtual T back() = 0;
	virtual void enqueue(const T& newValue) = 0;
	virtual void dequeue() = 0;
};

template<typename T>
class CraigQueue : public QueueADT<T>
{
private:
	int nodeCounter = 0;
	Node<T>* queueFront;
	Node<T>* queueBack;
public:
	bool isEmpty()
	{
		return queueFront == nullptr;
	}
	bool isFull()
	{
		return false;
	}
	int size()
	{
		return nodeCounter;
	}
	T front()
	{
		return queueFront->data;
	}
	T back()
	{
		return queueBack->data;
	}
	void enqueue(const T& newValue)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = newValue;
		newNode->link = nullptr;

		if (isEmpty())
		{
			queueFront = newNode;
			queueBack = newNode;
		}
		else
		{
			queueBack->link = newNode;
			queueBack = queueBack->link;
		}
		nodeCounter++;
	}
	void dequeue()
	{
		assert(!isEmpty());
		Node<T>* temp = queueFront;
		queueFront = queueFront->link;
		delete temp;
		nodeCounter--;
	}
	void printQueue()
	{
		Node<T>* current = new Node<T>;
		current = queueFront;

		for (int i = 0; i < nodeCounter; i++)
		{
			cout << current->data << endl;
			current = current->link;
		}
	}
	CraigQueue()
	{
		queueFront = nullptr;
		queueBack = nullptr;
		nodeCounter = 0;
	}
};