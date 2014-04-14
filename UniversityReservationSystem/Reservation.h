#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "Group.h"
#include "Teacher.h"
#include "IRoom.h"
#include <ctime>

using namespace std;

class Teacher;
class IRoom;
class Group;

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
		int dateStart = stoi(stringBuffer);

		getline(is, stringBuffer);
		int dateEnd = stoi(stringBuffer);

		getline(is, stringBuffer);
		int teacherId = stoi(stringBuffer);

		getline(is, stringBuffer);
		int roomId = stoi(stringBuffer);

		Teacher& teacher = context.Teachers.FindById(teacherId);
		IRoom& room = context.Rooms.FindById(roomId);

		return *(new Reservation(name, dateStart, dateEnd, teacher, room, id));
	}

	void Serialize(ostream& os) const
	{
		char _dateOfStart[25];
		char _dateOfEnd[25];

		strftime(_dateOfStart, 25, "%c", localtime(&DateOfStart));
		strftime(_dateOfEnd, 25, "%c", localtime(&DateOfEnd));

		ISerializable::Serialize(os);
		os << Name << endl
			<< _dateOfStart << endl
			<< _dateOfEnd << endl
			<< BoundTeacher.Id << endl
			<< Room.Id;
	}

	void Edit(Reservation reservationToEdit)
	{
		this->Name = reservationToEdit.Name;
	}

	bool CheckCollisions(Reservation& toCheck)
	{
		if ((toCheck.DateOfStart >= this->DateOfStart && toCheck.DateOfStart <= this->DateOfEnd) ||
			(this->DateOfStart >= toCheck.DateOfStart && this->DateOfStart <= this->DateOfEnd))
		{
			return true;
		}
		return false;
	}
};