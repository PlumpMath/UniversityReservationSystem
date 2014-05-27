#pragma once

using namespace std;

/* Abstract class which is the "highest" class in the UML tree. 
   and guarantees that every inherited class has capabilities
   resulting from this class. It is Id property and methods
   connected with this property */

class ISerializable
{
public:
	int Id;

	ISerializable()
	{
		Id = -1;
	}

	ISerializable(int id)
	{
		Id = id;
	}

	virtual void Serialize(ostream& os)
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

	friend ostream& operator<<(ostream& os, ISerializable& object)
	{
		object.Serialize(os);
		return os;
	}

	virtual ~ISerializable() = 0;
};

ISerializable::~ISerializable() { }