#pragma once
#include "TQueue.h"

using namespace std;

class Reservation;

template <class T>
class TAntiCollisionQueue : public TQueue<T>
{
public:
	bool CheckCollisions(Reservation& reservation)
	{
		bool collisionsDetected = false;

		for (int i = 0; i < list.size(); i++)
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
		for (int i = 0; i < list.size(); i++)
		{
			list[i]->AddReservation(reservation);
		}
	}
};