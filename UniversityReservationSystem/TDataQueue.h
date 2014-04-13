#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "CommonFactory.h"

using namespace std;

class DataContext;

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
	virtual bool Add(T& toAdd, bool isDataContext = false)
	{
		if (&toAdd != NULL)
		{
			if (isDataContext) toAdd.Id = GenerateId();

			list.push_back(&toAdd);
			return true;
		}
		else throw "Null pointer exception";
	}

	virtual bool Contains(T& toFind)
	{
		if (&toFind != NULL)
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == &toFind) return true;
			}
			return false;
		}
		else throw "Null pointer exception";
	}

	void Remove(T& toRemove)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == &toRemove)
			{
				list.erase(list.begin() + i);
				break;
			}
		}
	}
	
	void Delete(T& toDelete)
	{
		this->Remove(toDelete);
		delete &toDelete;
	}

	void DeleteRange(TDataQueue<T> * toDelete)
	{

	}

	void Clear()
	{
		for (int i = 0; i < list.size(); i++)
		{
			delete list[i];
		}
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

	void Deserialize(ifstream& is, DataContext& context)
	{
		int count = 0;
		is >> count;

		while (count--)
		{
			Add(CommonFactory::NewObject(is, context));
		}
	}

	template <class TT>
	friend ostream& operator<<(ostream& os, const TDataQueue<TT> &object);

	virtual ~TDataQueue() { }
};

template<class T>
ostream& operator<<(ostream& os, const TDataQueue<T> &object)
{
	// Putting the size of the collection in the beginning
	os << object.list.size() << endl;

	for (int i = 0; i < object.list.size(); i++)
	{
		os << *(object.list[i]) << endl;
	}

	return os;
}