#pragma once

#include "TQueue.h"
#include "Reservation.h"

using namespace std;

class Reservation;
class IPerson
{
public:
	string FirstName;
	string LastName;
	TQueue<Reservation> Reservations;

	IPerson(string _firstName, string _lastName)
	{
		FirstName = _firstName;
		LastName = _lastName;
	}

	virtual ~IPerson() = 0;
};

IPerson::~IPerson() { }