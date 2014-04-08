#pragma once

#include "Reservation.h"
#include "TQueue.h"

class Reservation;
class IRoom
{
public:
	int Id;
	string Name;
	int Capacity;
	TQueue<Reservation> Reservations;

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

	virtual ~IRoom();
};

IRoom::~IRoom() { }