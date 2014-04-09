#pragma once
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class TDataQueue
{
protected:
	std::vector<T*> list;
	
	int GenerateId()
	{
		int max = 0;

		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->Id > max) max = list[i]->Id;
		}
		return ++max;
	}

public:
	virtual bool Add(T* toAdd, bool isDataContext = false)
	{
		if (toAdd != NULL)
		{
			if (isDataContext) toAdd->Id = GenerateId();

			list.push_back(toAdd);
			return true;
		}
		else throw "Null pointer exception";
	}

	virtual bool Contains(T* toFind)
	{
		if (toFind != NULL)
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == toFind) return true;
			}
			return false;
		}
		else throw "Null pointer exception";
	}

	int Remove(T* toDelete)
	{
		int removed = 0;
		// From the end because every time we delete, indexes moves
		for (int i = list.size() - 1; i >= 0; i--)
		{
			if (list[i] == toDelete)
			{
				list.erase(list.begin() + i);
				removed++;
			}
		}
		return removed;
	}

	void Clear()
	{
		for (int i = 0; i < list.size(); i++)
		{
			delete list[i];
		}
	}

	bool Remove(int toDeleteIndex)
	{
		if (toDeleteIndex < Count())
		{
			list.erase(list.begin() + toDeleteIndex);
			return true;
		}
		else throw "Out of range exception";
	}

	int Count()
	{
		return list.size();
	}

	T& operator[] (int i)
	{
		if (i >= 0 && i < list.size())
		{
			return *list[i];
		}
		else throw "Out of range exception";
	}

	template <class TT>
	friend ostream& operator<<(ostream& os, const TDataQueue<TT> &object);

	template <class TT>
	friend ifstream& operator>>(ifstream& ifs, TDataQueue<TT> &object);

	virtual ~TDataQueue() { }
};

template<class T>
ostream& operator<<(ostream& os, const TDataQueue<T> &object)
{
	for (int i = 0; i < object.list.size(); i++)
	{
		os << *(object.list[i]) << endl;
	}

	return os;
}

template<class T>
ifstream& operator>>(ifstream& ifs, TDataQueue<T> &object)
{
	T *newObj = new T(ifs);


	return ifs;
}