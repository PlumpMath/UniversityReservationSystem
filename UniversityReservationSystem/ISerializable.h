#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ISerializable
{
public:
	int Id;

	ISerializable()
	{
		Id = -1;
	}

	ISerializable(int _id)
	{
		Id = _id;
	}

	virtual void Serialize(ostream& os) const
	{
		os << Id << endl;
	}

	bool operator==(const ISerializable& obj)
	{
		return this->Id == obj.Id;
	}

	bool operator!=(const ISerializable& obj)
	{
		return this->Id != obj.Id;
	}

	friend ostream& operator<<(ostream& os, ISerializable const& object)
	{
		object.Serialize(os);
		return os;
	}

	virtual ~ISerializable();
};

ISerializable::~ISerializable() { }