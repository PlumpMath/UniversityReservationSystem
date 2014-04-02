#pragma once

#include "Reservation.h"
#include "TQueue.h"

class IRoom
{
public:
	string Name;
	int Capacity;
	TQueue<Reservation> Reservations;

	IRoom(string _name, int _capacity)
	{
		Name = _name;
		Capacity = _capacity;
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(&reservationToAdd);
	}

	virtual ~IRoom() = 0;
};

IRoom::~IRoom() { }