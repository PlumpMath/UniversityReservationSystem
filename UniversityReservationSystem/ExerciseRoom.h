#pragma once

#include "IRoom.h"
#include <fstream>

using namespace std;

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

	//
	// Constructor used during deserialization
	//
	ExerciseRoom(string _name, int _capacity, int _numOfChairs, int _numOfTables, int _id)
		: IRoom(_name, "Exercise", _capacity, _id)
	{
		NumOfChairs = _numOfChairs;
		NumOfTables = _numOfTables;
	}

	static IRoom& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		int id = stoi(stringBuffer);

		getline(is, stringBuffer);
		string name = stringBuffer;

		getline(is, stringBuffer);
		int capacity = stoi(stringBuffer);

		getline(is, stringBuffer);
		int numChairs = stoi(stringBuffer);

		getline(is, stringBuffer);
		int numTables = stoi(stringBuffer);

		return *(new ExerciseRoom(name, capacity, numChairs, numTables, id));
	}

	void Edit(ExerciseRoom& roomToEdit)
	{
		IRoom::Edit(roomToEdit);
		this->NumOfChairs = roomToEdit.NumOfChairs;
		this->NumOfTables = roomToEdit.NumOfTables;
	}

	void Serialize(ostream& os) 
	{
		IRoom::Serialize(os);
		os << NumOfChairs << endl
			<< NumOfTables;
	}
};