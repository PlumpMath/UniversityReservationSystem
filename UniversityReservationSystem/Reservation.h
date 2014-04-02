#pragma once

#include "TQueue.h"
//#include "Group.h"
//#include "Teacher.h"

using namespace std;

class Reservation
{
public:
	string Name;
	int DateOfStart;
	int DateOfEnd;
	Teacher& BoundTeacher;
	TQueue<Group> BoundGroups;

	Reservation(string _name, int _dateOfStart, int _dateOfEnd, Teacher& _teacher)
		: BoundTeacher(_teacher)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
	}
};