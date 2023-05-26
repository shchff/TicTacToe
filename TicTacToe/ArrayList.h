#pragma once
#include <iostream>

using namespace std;

template <class T>
class ArrayList
{
public:
	T* pData;
	ArrayList();
	~ArrayList();
	void Print() const;
	int Length() const;
	bool IsEmpty();
	T& Get(int idx) const;
	void Append(T element);
	bool InsertAt(T element, int idx);
	bool DeleteAt(int idx);
	T operator[](int idx);
	void Copy(T* pTemp);
private:
	void Resize();
	int capacity;
	int size;
	int growFactor;
};

template <class T>
ArrayList<T>::ArrayList()
{
	size = 0;
	capacity = 4;
	growFactor = 2;
	pData = new T[capacity];
}

template <class T>
ArrayList<T>::~ArrayList()
{
	delete[] pData;
}
template <class T>
void ArrayList<T>::Print() const
{
	for (int i = 0; i < size; i++)
	{
		cout << pData[i] << " ";
	}
	cout << endl;
}

template <class T>
int ArrayList<T>::Length() const
{
	return size;
}

template <class T>
bool ArrayList<T>::IsEmpty()
{
	return Length() == 0;
}

template <class T>
T& ArrayList<T>::Get(int idx) const
{

	if (idx < 0 || idx >= size)
	{
		cout << "error" << endl;
		return pData[0];
	}
	else {
		return pData[idx];
	}
}

template <class T>
void ArrayList<T>::Append(T element)
{
	if (size == capacity)
	{
		Resize();
	}
	pData[size++] = element;

}

template <class T>
bool ArrayList<T>::InsertAt(T element, int idx)
{
	if (idx < 0 || idx >= size)
		return false;

	if (size == capacity)
		Resize();

	for (int i = size; i > idx; i--)
		pData[i] = pData[i - 1];

	pData[idx] = element;
	size++;
	return true;
}

template <class T>
bool ArrayList<T>::DeleteAt(int idx)
{
	if (idx < 0 || idx >= size)
		return false;

	for (int i = idx; i < size - 1; i++)
		pData[i] = pData[i + 1];
	size--;
	return true;
}

template <class T>
T ArrayList<T>::operator[](int idx)
{
	return Get(idx);
}

template <class T>
void ArrayList<T>::Resize()
{
	capacity = capacity * growFactor;
	T* pTemp = new T[capacity];
	Copy(pTemp);
	delete[] pData;
	pData = pTemp;
}

template <class T>
void ArrayList<T>::Copy(T* pTemp)
{
	for (int i = 0; i < size; i++)
	{
		pTemp[i] = pData[i];
	}
}