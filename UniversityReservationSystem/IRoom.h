#pragma once

#include "TAntiCollisionQueue.h"
#include "ISerializable.h"

class DataContext;
class Reservation;

class IRoom : public ISerializable
{
public:
	string Name;
	string Type;
	int Capacity;
	TAntiCollisionQueue<Reservation> Reservations;

	IRoom(string _name, string _type, int _capacity)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	IRoom(string _name, string _type, int _capacity, int _id)
		: ISerializable(_id)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	// should be never invoked
	static IRoom& Deserialize(ifstream& is, DataContext& context){ throw 1; }

	virtual void Edit(IRoom roomToEdit)
	{
		this->Name = roomToEdit.Name;
		this->Capacity = roomToEdit.Capacity;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		return Reservations.CheckCollisions(reservation);
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(reservationToAdd);
	}

	void RemoveReservation(Reservation &reservationToRemove)
	{
		Reservations.Remove(reservationToRemove);
	}

	virtual void Serialize(ostream& os) const
	{
		os << Type << endl;
		ISerializable::Serialize(os);
		os << Name << endl
			<< Capacity << endl;
	}

	virtual ~IRoom();
};

IRoom::~IRoom() { }