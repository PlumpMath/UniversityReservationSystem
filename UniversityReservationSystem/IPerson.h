#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "Reservation.h"
#include <string>
#include <fstream>

using namespace std;
class Reservation;

class IPerson : public ISerializable
{
public:
	string FirstName;
	string LastName;
	string Type;
	TAntiCollisionQueue<Reservation> Reservations;

	IPerson(string _firstName, string _lastName, string _type)
	{
		FirstName = _firstName;
		LastName = _lastName;
		Type = _type;
	}

	IPerson(ifstream& is, string type) : ISerializable(is), Type(type)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		FirstName = stringBuffer;

		getline(is, stringBuffer);
		LastName = stringBuffer;
	}

	virtual bool CheckCollisions(Reservation& reservation)
	{
		return Reservations.CheckCollisions(reservation);
	}

	void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(reservationToAdd);
	}

	virtual void Serialize(ostream& os) const
	{
		os << Type << endl;
		ISerializable::Serialize(os);
		os << FirstName << endl
			<< LastName << endl;
	}

	virtual ~IPerson();
};

IPerson::~IPerson() { }