#pragma once

#include "TQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "IPerson.h"
#include "IRoom.h"

class DataContext
{
public:
	TQueue<IPerson> People;
	TQueue<IRoom> Rooms;
	TQueue<Group> Groups;
	TQueue<Reservation> Reservations;

	void SaveChanges()
	{
		// TODO: Serialize + save to files
	}
};