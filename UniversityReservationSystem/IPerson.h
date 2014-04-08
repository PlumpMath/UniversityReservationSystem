#pragma once

#include "TQueue.h"
#include "Reservation.h"

using namespace std;

class Reservation;
class IPerson
{
public:
	int Id = -1;
	string FirstName;
	string LastName;
	TQueue<Reservation> Reservations;

	IPerson(string _firstName, string _lastName)
	{
		FirstName = _firstName;
		LastName = _lastName;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		return false;
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(&reservationToAdd);
	}



	virtual ~IPerson() = 0;
};

IPerson::~IPerson() { }