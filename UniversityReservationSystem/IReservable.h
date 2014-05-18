#pragma once

#include "ISerializable.h"

using namespace std;

class IReservable : public ISerializable
{
public:
	IReservable()
		: ISerializable() { }

	IReservable(int id)
		: ISerializable(id) { }

	TAntiCollisionQueue<Reservation> Reservations;
	virtual ~IReservable();
};

IReservable::~IReservable() { }