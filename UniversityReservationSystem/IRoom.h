#pragma once

#include "ISerializable.h"
#include "Reservation.h"
#include "TAntiCollisionQueue.h"
#include <fstream>

class Reservation;

class IRoom : public ISerializable
{
public:
	string Name;
	string Type;
	int Capacity;
	TAntiCollisionQueue<Reservation> Reservations;

	IRoom(string _name, string _type, int _capacity)
	{
		Name = _name;
		Type = _type;
		Capacity = _capacity;
	}

	IRoom(ifstream& is, string type) : ISerializable(is), Type(type)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		Name = stringBuffer;

		getline(is, stringBuffer);
		Capacity = stoi(stringBuffer);
	}

	bool CheckCollisions(Reservation& reservation)
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
		os << Name << endl
			<< Capacity << endl;
	}

	virtual ~IRoom();
};

IRoom::~IRoom() { }