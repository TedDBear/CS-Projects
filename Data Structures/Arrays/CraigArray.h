#pragma once
#include <iostream>
#include <assert.h>
#include <array>
#include <string>

using namespace std;

template <typename T, int elementCount>

class CraigArray
{
private:
	T data[elementCount];
public:
	/// <summary>
	/// Returns element Count ...
	/// <returns></returns>the element count
	int getElementCount()
	{
		return elementCount;
	}
	/// <summary>
	/// returns the element at a particular position
	/// <param name="index"></param>
	/// <returns></returns>the element at a particular position
	T getElementAt(int index)
	{
		assert(index >= 0);

		return data[index];
	}
	/// <summary>
	/// modifies an element at a particular position
	/// <param name="index"></param>
	/// <param name="dataItem"></param>
	void modifyElement(int index, T dataItem)
	{
		data[index] = dataItem;
	}
	/// <summary>
	/// swaps two elements' places
	/// <param name="index1"></param>
	/// <param name="index2"></param>
	void swap(int index1, int index2)
	{
		T temp = data[index1];
		data[index1] = data[index2];
		data[index2] = temp;
	}
	/// <summary>
	/// prints all of the elements in the array 
	/// <param name="elementCount"></param>
	void printArray()
	{
		for (int i = 0; i < elementCount; i++)
		{
			cout << data[i] << " ";
		}
		cout << endl;
	}
	/// <summary>
	/// prints an element at a particular position
	/// <param name="index"></param>
	void printAnElement(int index)
	{
		cout << data[index] << endl;
	}
	/// <summary>
	/// uses the operator [] to return a element at a particular position
	/// <param name="index"></param>
	/// <returns></returns>the element at a particular position
	T operator [] (int index)
	{
		return data[index]; 
	}
	

};



	
