#pragma once
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

template<typename T>

class CraigVector
{
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
public:
	void allocate(size_t newCapacity)
	{
		T* newBlock = new T[newCapacity];

		if (newCapacity < m_Size)
		{
			m_Size = newCapacity;
		}

		for (size_t i = 0; i < m_Size; i++)
		{
			newBlock[i] = m_Data[i];
		}

		delete[] m_Data;

		m_Data = newBlock;

		m_Capacity = newCapacity;

	}

	void push_back(const T& value)
	{
		if (m_Size >= m_Capacity)
		{
			allocate(2 * m_Capacity);
			cout << "Increasing capacity to " << m_Capacity << endl;
		}

		m_Data[m_Size] = value;
		m_Size++;
	}

	void pop_back()
	{
		assert(m_Size > 0);
		m_Size--;
		T poppedElement = m_Data[m_Size];
		m_Data[m_Size].~T();
	};

	/// <summary>
	/// swaps the places of 2 elements
	/// </summary>
	/// <param name="index1"></param>
	/// <param name="index2"></param>
	void swap(size_t index1, size_t index2)
	{
		assert(index1 < m_Size && index2 < m_Size);
		T temp = m_Data[index1];
		m_Data[index1] = m_Data[index2];
		m_Data[index2] = temp;
	}

	/// <summary>
	/// deletes an element at a particular position
	/// </summary>
	/// <param name="index"></param>
	void deleteAt(size_t index)
	{
		assert(index < m_Size);
		if (index >= m_Size - 1)
		{
			pop_back();
		}
		else 
		{
			swap(index, m_Size - 1);
			pop_back();
			swap(m_Size - 1, index);
		}
	}

	/// <summary>
	/// inserts an element at a particular position 
	/// </summary>
	/// <param name="value"></param>
	/// <param name="index"></param>
	void insertAt(const T& value, size_t index)
	{
		assert(index <= m_Size);
		push_back(value);
		for (size_t i = m_Size - 1; i > index; i--)
		{
			swap(i, i - 1);
		}
	}

	/// <summary>
	/// Brings an element at a particular position to the front of the vector
	/// </summary>
	/// <param name="index"></param>
	void bringToFront(size_t index)
	{
		assert(index < m_Size);
		for (size_t i = index; i > 0; i--)
		{
			swap(i, i - 1);
		}
	}

	/// <summary>
	/// Brings an element at a particular position to the back of the vector
	/// </summary>
	/// <param name="index"></param>
	void bringToBack(size_t index)
	{
		assert(index < m_Size);
		for (size_t i = index; i < m_Size - 1; i++)
		{
			swap(i, i + 1);
		}

	}

	void clear()
	{
		while (m_Size > 0)
		{
			pop_back(); 
		}
	}

	T* getVector()
	{
		return m_Data;
	}

	size_t getSize()
	{
		return m_Size;
	}

	size_t getCapacity()
	{
		return m_Capacity;
	}

	void print()
	{
		for (int i = 0; i < m_Size; i++)
		{
			cout << "\nItem #" << i + 1 << ": ";
			cout << m_Data[i] << " ";
		}
		cout << endl;
	}

	CraigVector()
	{
		allocate(2);
	}

	/// <summary>
	/// copies a vector onto another vector
	/// </summary>
	/// <param name="otherVector"></param>
	CraigVector(const CraigVector& otherVector)
	{
		m_Size = otherVector.m_Size;
		m_Capacity = otherVector.m_Capacity;
		m_Data = new T[m_Size];
		for (size_t i = 0; i < m_Size; i++)
		{
			m_Data[i] = otherVector.m_Data[i];
		}

	}

	~CraigVector()
	{
		clear();
		delete[] m_Data;
	}

	T& operator[](size_t index)
	{
		assert(index <= m_Capacity - 1);
		return m_Data[index];
	}


};
