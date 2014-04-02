#include <string>
#include <vector>
#include "Group.h"
#include "Teacher.h"
using namespace std;

class Reservation
{
protected:
	string Name;
	int DateOfStart;
	int DateOfEnd;
	Teacher& BoundTeacher;
	vector<Group> GroupofPeople;

	Reservation(string _name, int _dateOfStart, int _dateOfEnd, Teacher& _teacher)
	{
		Name = _name;
		DateOfStart = _dateOfStart;
		DateOfEnd = _dateOfEnd;
		BoundTeacher = _teacher;
	}
};