#pragma once

using namespace std;

class ISerializable
{
public:
	int Id;

	ISerializable()
	{
		Id = -1;
	}


	virtual void Serialize(ostream& os) const
	{
		os << Id << endl;
	}

	friend ostream& operator<<(ostream& os, ISerializable const& object)
	{
		object.Serialize(os);
		return os;
	}

	virtual ~ISerializable();
};

ISerializable::~ISerializable() { }