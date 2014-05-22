#pragma once

#include "TAntiCollisionQueue.h"
#include "IReservable.h"
#include "ISerializable.h"

class IRoom : public IReservable
{
public:
	string Name;
	string Type;
	int Capacity;

	IRoom(string _name, string _type, int _capacity)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	//
	// Constructor used during deserialization
	//
	IRoom(string _name, string _type, int _capacity, int _id)
		: IReservable(_id)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	// should be never invoked
	static IRoom& Deserialize(ifstream& is, DataContext& context){ throw 1; }

	virtual void Edit(IRoom& roomToEdit)
	{
		this->Name = roomToEdit.Name;
		this->Capacity = roomToEdit.Capacity;
	}

	virtual void Serialize(ostream& os)
	{
		os << Type << endl;
		ISerializable::Serialize(os);
		os << Name << endl
			<< Capacity << endl;
	}

	virtual ~IRoom() = 0;
};

IRoom::~IRoom() { }