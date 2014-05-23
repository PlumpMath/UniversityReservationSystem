#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TAntiCollisionQueue.h"

using namespace std;

class Reservation;

class IPerson : public IReservable
{
public:
	string FirstName;
	string LastName;

	IPerson(string _firstName, string _lastName)
	{
		FirstName = _firstName;
		LastName = _lastName;
	}

	//
	// Constructor used during deserialization
	//
	IPerson(string _firstName, string _lastName, int _id)
		: IReservable(_id)
	{
		FirstName = _firstName;
		LastName = _lastName;
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

	virtual ~IPerson() = 0;
};

IPerson::~IPerson() { }