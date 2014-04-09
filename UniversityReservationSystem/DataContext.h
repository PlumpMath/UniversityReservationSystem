#pragma once

#include "TDataQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "IPerson.h"
#include "IRoom.h"
#include <fstream>

#define GROUPS_FILE "groups.txt"
#define PEOPLE_FILE "people.txt"
#define ROOMS_FILE "rooms.txt"
#define RESERVATIONS_FILE "reservations.txt"

using namespace std;

class DataContext
{
protected:
	string filePath;
public:
	TDataQueue<Group> Groups;
	TDataQueue<IPerson> People;
	TDataQueue<IRoom> Rooms;
	TDataQueue<Reservation> Reservations;

	DataContext(string _filePath)
	{
		filePath = _filePath;
		TryLoadTheBase();
	}

	void SaveChanges()
	{
		ofstream fileGroups(filePath + "//" + GROUPS_FILE, ofstream::trunc);
		ofstream filePeople(filePath + "//" + PEOPLE_FILE, ofstream::trunc);
		ofstream fileRooms(filePath + "//" + ROOMS_FILE, ofstream::trunc);
		ofstream fileReservations(filePath + "//" + RESERVATIONS_FILE, ofstream::trunc);

		fileGroups.clear();
		fileGroups << Groups;
		fileGroups.close();

		filePeople.clear();
		filePeople << People;
		filePeople.close();

		fileRooms.clear();
		fileRooms << Rooms;
		fileRooms.close();

		fileReservations.clear();
		fileReservations << Reservations;
		fileReservations.close();
	}

	void TryLoadTheBase()
	{
		ifstream fileGroups(filePath + "//" + GROUPS_FILE);
		ifstream filePeople(filePath + "//" + PEOPLE_FILE);
		ifstream fileRooms(filePath + "//" + ROOMS_FILE);
		ifstream fileReservations(filePath + "//" + RESERVATIONS_FILE);

		fileGroups >> Groups;
		fileGroups.close();

		filePeople >> People;
		filePeople.close();

		fileRooms >> Rooms;
		fileRooms.close();

		fileReservations >> Reservations;
		fileReservations.close();
	}

	void Clear()
	{
		People.Clear();
		Rooms.Clear();
		Groups.Clear();
		Reservations.Clear();
	}
};