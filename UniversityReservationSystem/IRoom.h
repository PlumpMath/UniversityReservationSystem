#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TDataQueue.h"

class Reservation;

class IRoom : public ISerializable
{
public:
	string Name;
	int Capacity;
	TDataQueue<Reservation> Reservations;

	IRoom(string _name, int _capacity)
	{
		Name = _name;
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
		os << " " << Capacity;
	}

	virtual ~IRoom();
};

IRoom::~IRoom() { }