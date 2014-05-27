#pragma once

#include "ISerializable.h"

using namespace std;

/* Abstract class which describes an every reservable
   class and its capabilities and methods */

class IReservable : public ISerializable
{
public:
	TAntiCollisionQueue<Reservation> Reservations;

	IReservable()
		: ISerializable() { }

	IReservable(int id)
		: ISerializable(id) { }

	virtual bool CheckCollisions(Reservation& reservationToCheck)
	{
		return Reservations.CheckCollisions(reservationToCheck);
	}

	virtual void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(reservationToAdd);
	}

	virtual void RemoveReservation(Reservation &reservationToRemove)
	{
		Reservations.Remove(reservationToRemove);
	}

	virtual ~IReservable() = 0;
};

IReservable::~IReservable() { }