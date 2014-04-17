#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "DataContext.h"
#include "IRoom.h"
#include "Group.h"
#include "Teacher.h"

using namespace std;

class Reservation : public ISerializable
{
public:
	string Name;
	time_t DateOfStart;
	time_t DateOfEnd;
	Teacher& BoundTeacher;
	TAntiCollisionQueue<Group> BoundGroups;
	IRoom& Room;

	Reservation(string _name, time_t _dateOfStart, time_t _dateOfEnd, Teacher& _teacher, IRoom& _room)
		: BoundTeacher(_teacher), Room(_room)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
	}

	//
	// Constructor used during deserialization
	//
	Reservation(string _name, time_t _dateOfStart, time_t _dateOfEnd, Teacher& _teacher, IRoom& _room, int _id)
		: ISerializable(_id), BoundTeacher(_teacher), Room(_room)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
	}

	static Reservation& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		int id = stoi(stringBuffer);

		getline(is, stringBuffer);
		string name = stringBuffer;

		getline(is, stringBuffer);
		time_t dateStart = stoi(stringBuffer);

		getline(is, stringBuffer);
		time_t dateEnd = stoi(stringBuffer);

		getline(is, stringBuffer);
		int teacherId = stoi(stringBuffer);

		getline(is, stringBuffer);
		int roomId = stoi(stringBuffer);

		getline(is, stringBuffer);
		int numOfBoundGroups = stoi(stringBuffer);

		Teacher& teacher = context.Teachers.FindById(teacherId);
		IRoom& room = context.Rooms.FindById(roomId);

		Reservation * toAdd = new Reservation(name, dateStart, dateEnd, teacher, room, id);
		
		while (numOfBoundGroups--)
		{
			getline(is, stringBuffer);
			int groupID = stoi(stringBuffer);
			toAdd->BoundGroups.Add(context.Groups.FindById(groupID));
		}

		return *toAdd;
	}

	void Serialize(ostream& os)
	{
		int numOfBoundGroups = BoundGroups.Count();

		ISerializable::Serialize(os);
		os << Name << endl
			<< DateOfStart << endl
			<< DateOfEnd << endl
			<< BoundTeacher.Id << endl
			<< Room.Id << endl
			<< numOfBoundGroups;

		// writing reservation's bound groups' IDs 
		for (int i = 0; i < numOfBoundGroups; i++)
		{
			os << endl << BoundGroups[i].Id;
		}
	}

	void Edit(Reservation reservationToEdit)
	{
		this->Name = reservationToEdit.Name;
	}

	//
	// Checking if 'toCheck' date of reservation collides with the object's date of reservation
	//
	bool CheckCollisions(Reservation& toCheck)
	{
		return ((toCheck.DateOfStart >= this->DateOfStart && toCheck.DateOfStart <= this->DateOfEnd) ||
			(this->DateOfStart >= toCheck.DateOfStart && this->DateOfStart <= this->DateOfEnd));
	}
};