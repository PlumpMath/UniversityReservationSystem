#pragma once

#include "ISerializable.h"
#include "TDataQueue.h"
#include "Reservation.h"

using namespace std;
class Reservation;

class IPerson : public ISerializable
{
public:
	string FirstName;
	string LastName;
	TDataQueue<Reservation> Reservations;

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

	virtual void Serialize(ostream& os) const
	{
		ISerializable::Serialize(os);
		os << " " << FirstName << " " << LastName;
	}

	virtual ~IPerson();
};

IPerson::~IPerson() { }