#pragma once

#include "TQueue.h"
#include "Group.h"
#include "Teacher.h"
#include "IRoom.h"
#include <ctime>

using namespace std;

class Group;
class Teacher;
class IRoom;
class Reservation
{
public:
	string Name;
	time_t DateOfStart;
	time_t DateOfEnd;
	Teacher& BoundTeacher;
	TQueue<Group> BoundGroups;
	IRoom& Room;


	Reservation(string _name, time_t _dateOfStart, time_t _dateOfEnd, Teacher& _teacher, IRoom& _room)
		: BoundTeacher(_teacher), Room(_room)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
		cout << ctime(&DateOfStart) << endl;
		cout << ctime(&DateOfEnd);
	}
};