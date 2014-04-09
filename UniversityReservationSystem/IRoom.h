#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TDataQueue.h"

class Reservation;

class IRoom : public ISerializable
{
public:
	string Name;
	string Type;
	int Capacity;
	TDataQueue<Reservation> Reservations;

	IRoom(string _name, string _type, int _capacity)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		return false;
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(&reservationToAdd);
	}

	virtual void Serialize(ostream& os) const
	{
		ISerializable::Serialize(os);
		os << Type << endl
			<< Name << endl
			<< Capacity << endl;
	}

	virtual ~IRoom();
};

IRoom::~IRoom() { }