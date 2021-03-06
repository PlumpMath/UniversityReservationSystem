#pragma once

#include "ControllerFactory.h"

using namespace std;

/* Queue-generic-class which is responsible for storing
objects of model classes. Besides has a lot of method
to handle encapsulated STL vector property */

template <class T>
class TDataQueue
{
protected:
	std::vector<T*> list;
	
	int GenerateId()
	{
		int max = 0;

		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (list[i]->Id > max) max = list[i]->Id;
		}
		return ++max;
	}

public:
	bool Add(T& toAdd, bool newRecord = false)
	{
		if (newRecord) toAdd.Id = GenerateId();

		list.push_back(&toAdd);
		return true;
	}

	T& Find(T& toFind)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (*list[i] == toFind) return *list[i];
		}
		throw "Null pointer exception";
	}

	T& FindById(int id)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if ((*list[i]).Id == id) return *list[i];
		}
		throw "Null pointer exception";
	}

	void AddRange(TDataQueue<T>& toAdd)
	{
		for (unsigned int i = 0; i < toAdd.Count(); i++)
		{
			this->Add(toAdd[i]);
		}
	}

	void Remove(T& toRemove)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (*list[i] == toRemove)
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

	void Clear(bool withoutDeleting = false)
	{
		if (withoutDeleting)
		{
			list.clear();
			return;
		}

		for (unsigned int i = 0; i < list.size(); i++)
		{
			delete list[i];
		}
	}

	unsigned int Count()
	{
		return list.size();
	}

	T& operator[] (unsigned int i)
	{
		if (i >= 0 && i < list.size())
		{
			return *list[i];
		}
		else throw "Out of range exception";
	}

	void Deserialize(ifstream& is, DataContext& context)
	{
		string type = typeid(T).name();

		IController<T>& factory
			= ControllerFactory<T>::CreateController(context, type);

		string buffer;
		getline(is, buffer);
		int count = stoi(buffer);

		if (type == "class IRoom")
		{
			while (count-- > 0)
			{
				factory.Add(*dynamic_cast<T*>(&RoomFactory::CreateObject(is, context)));
			}
		}
		else
		{
			while (count-- > 0)
			{
				factory.Add(T::Deserialize(is, context));
			}
		}
		

		delete &factory;
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

	for (unsigned int i = 0; i < object.list.size(); i++)
	{
		os << *(object.list[i]) << endl;
	}

	return os;
}