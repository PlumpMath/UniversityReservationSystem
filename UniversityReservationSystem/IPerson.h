#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TAntiCollisionQueue.h"

using namespace std;

class Reservation;

class IPerson : public ISerializable
{
public:
	string FirstName;
	string LastName;
	TAntiCollisionQueue<Reservation> Reservations;

	IPerson(string _firstName, string _lastName)
	{
		FirstName = _firstName;
		LastName = _lastName;
	}

	//
	// Constructor used during deserialization
	//
	IPerson(string _firstName, string _lastName, int _id)
		: ISerializable(_id)
	{
		FirstName = _firstName;
		LastName = _lastName;
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

	virtual void Edit(IPerson& personToEdit)
	{
		this->FirstName = personToEdit.FirstName;
		this->LastName = personToEdit.LastName;
	}

	virtual void Serialize(ostream& os)
	{
		ISerializable::Serialize(os);
		os << FirstName << endl
			<< LastName << endl;
	}

	virtual ~IPerson();
};

IPerson::~IPerson() { }