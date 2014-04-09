#pragma once

#include "TDataQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "IPerson.h"
#include "IRoom.h"
#include <fstream>

using namespace std;

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
		ofstream filePeople(filePath + "//people.txt", ofstream::trunc);
		ofstream fileRooms(filePath + "//rooms.txt", ofstream::trunc);
		ofstream fileGroups(filePath + "//groups.txt", ofstream::trunc);
		ofstream fileReservations(filePath + "//reservations.txt", ofstream::trunc);

		filePeople.clear();
		filePeople << People;
		filePeople.close();

		fileRooms.clear();
		fileRooms << Rooms;
		fileRooms.close();

		fileGroups.clear();
		fileGroups << Groups;
		fileGroups.close();

		fileReservations.clear();
		fileReservations << Reservations;
		fileReservations.close();
	}

	void TryLoadTheBase()
	{
		// TODO: Deserialize + load to the memory
	}
};