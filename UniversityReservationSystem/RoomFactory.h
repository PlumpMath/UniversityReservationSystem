#pragma once

#include "ExerciseRoom.h"
#include "LabRoom.h"

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