#pragma once

#include "TDataQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "IPerson.h"
#include "IRoom.h"

class DataContext
{
protected:
	string filePath;
public:
	TDataQueue<IPerson> People;
	TDataQueue<IRoom> Rooms;
	TDataQueue<Group> Groups;
	TDataQueue<Reservation> Reservations;

	DataContext(string _filePath)
	{
		filePath = _filePath;
		TryLoadTheBase();
	}

	void SaveChanges()
	{
		
	}

	void TryLoadTheBase()
	{
		// TODO: Deserialize + load to the memory
	}
};