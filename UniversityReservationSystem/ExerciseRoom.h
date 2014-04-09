#pragma once

#include "IRoom.h"
#include <fstream>

class ExerciseRoom : public IRoom
{
public:
	int NumOfChairs;
	int NumOfTables;

	ExerciseRoom(string _name, int _capacity, int _numOfChairs, int _numOfTables)
		: IRoom(_name, "Exercise", _capacity)
	{
		NumOfChairs = _numOfChairs;
		NumOfTables = _numOfTables;
	}

	ExerciseRoom(ifstream& is) : IRoom(is, "Exercise")
	{
		string stringBuffer;

		getline(is, stringBuffer);
		NumOfChairs = stoi(stringBuffer);

		getline(is, stringBuffer);
		NumOfTables = stoi(stringBuffer);
	}

	void Serialize(ostream& os) const 
	{
		IRoom::Serialize(os);
		os << NumOfChairs << endl
			<< NumOfTables;
	}
};