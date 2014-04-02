#pragma once

#include "IRoom.h"

class LabRoom : public IRoom
{
public:
	string AdditionalEquipment;
	int NumOfComputers;

	LabRoom(string _name, int _capacity, string _additionalEquipment, int _numOfComputers)
		: IRoom(_name, _capacity)
	{
		AdditionalEquipment = _additionalEquipment;
		NumOfComputers = _numOfComputers;
	}
};