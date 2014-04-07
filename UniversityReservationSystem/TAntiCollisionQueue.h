#pragma once

#include "TQueue.h"
#include "Reservation.h"

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
};