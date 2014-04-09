#pragma once

#include "ISerializable.h"
#include "TDataQueue.h"
#include "Reservation.h"
#include <string>

using namespace std;
class Reservation;

class IPerson : public ISerializable
{
public:
	string FirstName;
	string LastName;
	string Type;
	TDataQueue<Reservation> Reservations;

	IPerson(string _firstName, string _lastName, string _type)
	{
		FirstName = _firstName;
		LastName = _lastName;
		Type = _type;
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
			<< FirstName << endl
			<< LastName << endl;
	}

	virtual ~IPerson();
};

IPerson::~IPerson() { }