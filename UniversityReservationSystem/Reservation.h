#pragma once

#include "TQueue.h"
#include "Group.h"
#include "Teacher.h"
#include "IRoom.h"

using namespace std;

class Group;
class Teacher;
class IRoom;
class Reservation
{
public:
	string Name;
	int DateOfStart;
	int DateOfEnd;
	Teacher& BoundTeacher;
	TQueue<Group> BoundGroups;
	IRoom& Room;

	Reservation(string _name, int _dateOfStart, int _dateOfEnd, Teacher& _teacher, IRoom& _room)
		: BoundTeacher(_teacher), Room(_room)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
	}
};