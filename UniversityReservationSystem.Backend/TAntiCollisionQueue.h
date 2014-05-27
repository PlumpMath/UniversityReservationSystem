#pragma once

#include "TDataQueue.h"

using namespace std;

class Reservation;

/* Extends the basic queue-generic-class and adds methods
   which queue of every reservable class should have */

template <class T>
class TAntiCollisionQueue : public TDataQueue<T>
{
public:
	bool CheckCollisions(Reservation& reservation)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (!(list[i]->CheckCollisions(reservation)))
			{
				return false;
			}
		}

		return true;
	}

	void AddReservation(Reservation & reservation)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			list[i]->AddReservation(reservation);
		}
	}

	void RemoveReservation(Reservation & reservation)
	{
		for (unsigned int i = 0; i < list.size(); i++)
		{
			list[i]->RemoveReservation(reservation);
		}
	}

	T** GetArrayOfPointers()
	{
		T** toReturn = new T*[this->Count()];

		for (unsigned int i = 0; i < this->Count(); i++)
		{
			toReturn[i] = &((*this)[i]);
		}

		return toReturn;
	}
};