#pragma once

#include "TQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "IPerson.h"
#include "IRoom.h"

class DataContext
{
private:
	string filePath;
public:
	TQueue<IPerson> People;
	TQueue<IRoom> Rooms;
	TQueue<Group> Groups;
	TQueue<Reservation> Reservations;

	DataContext(string _filePath)
	{
		filePath = _filePath;
		TryLoadTheBase();
	}

	void SaveChanges()
	{
		// TODO: Serialize + save to files
	}

	void TryLoadTheBase()
	{
		// TODO: Deserialize + load to the memory
	}
};