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
	virtual bool Add(T& toAdd, bool newRecord = false)
	{
		if (newRecord) toAdd.Id = GenerateId();

		list.push_back(&toAdd);
		return true;
	}

	T& Find(T& toFind)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->Id == toFind.Id) return *list[i];
		}
		throw "Null pointer exception";
	}

	void Remove(T& toRemove)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->Id == toRemove.Id)
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

	/*void Deserialize(ifstream& is, DataContext& context)
	{
		string type = typeid(T).name();
		int count = 0;
		is >> count;

		while (count--)
		{
			ISerializable* toAdd = CommonFactory::NewObject(is, context, type);
			Add(*(dynamic_cast<T*>(toAdd)));
		}
	}*/

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