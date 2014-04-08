#pragma once

#include "IRoom.h"

class ExerciseRoom : public IRoom
{
public:
	int NumOfChairs;
	int NumOfTables;

	ExerciseRoom(string _name, int _capacity, int _numOfChairs, int _numOfTables)
		: IRoom(_name, _capacity)
	{
		NumOfChairs = _numOfChairs;
		NumOfTables = _numOfTables;
	}

	void Serialize(ostream& os) const 
	{
		IRoom::Serialize(os);
		os << " " << NumOfChairs << " " << NumOfTables;
	}
};