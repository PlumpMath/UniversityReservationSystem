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

	IPerson(string _firstName, string _lastName)
	{
		FirstName = _firstName;
		LastName = _lastName;

	}

	IPerson(ifstream& is) : ISerializable(is)
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

	virtual void AddReservation(Reservation &reservationToAdd)
	{
		Reservations.Add(reservationToAdd);
	}

	virtual void RemoveReservation(Reservation &reservationToRemove)
	{
		Reservations.Remove(reservationToRemove);
	}

	virtual void Edit(IPerson personToEdit)
	{
		this->FirstName = personToEdit.FirstName;
		this->LastName = personToEdit.LastName;
	}

	virtual void Serialize(ostream& os) const
	{
		ISerializable::Serialize(os);
		os << FirstName << endl
			<< LastName << endl;
	}

	virtual ~IPerson();
};

IPerson::~IPerson() { }