#pragma once

#include "TDataQueue.h"

using namespace std;

class Reservation;

template <class T>
class TAntiCollisionQueue : public TDataQueue<T>
{
public:
	bool CheckCollisions(Reservation& reservation)
	{
		bool collisionsDetected = false;

		for (unsigned int i = 0; i < list.size(); i++)
		{
			if (list[i]->CheckCollisions(reservation))
			{
				collisionsDetected;
				break;
			}
		}

		return collisionsDetected;
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
};