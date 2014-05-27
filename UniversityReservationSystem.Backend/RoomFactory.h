#pragma once

#include "ExerciseRoom.h"
#include "LabRoom.h"

/* Class responsible for invoking appropriate deserializer-class
   depending on the first line in input file stream in parameter */

class RoomFactory
{
public:
	static IRoom& CreateObject(ifstream& is, DataContext& context)
	{
		string type;
		getline(is, type);

		if (type == "Exercise")
		{
			return ExerciseRoom::Deserialize(is, context);
		}
		else //if (type == "Lab")
		{
			return LabRoom::Deserialize(is, context);
		}
	}
};