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
};