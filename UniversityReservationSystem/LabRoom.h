#pragma once

#include "IRoom.h"
#include <fstream>

class LabRoom : public IRoom
{
public:
	string AdditionalEquipment;
	int NumOfComputers;
	
	LabRoom(string _name, int _capacity, string _additionalEquipment, int _numOfComputers)
		: IRoom(_name, "Lab",  _capacity)
	{
		AdditionalEquipment = _additionalEquipment;
		NumOfComputers = _numOfComputers;
	}

	/*LabRoom(ifstream& is) : IRoom(is, "Lab")
	{
		string stringBuffer;

		getline(is, stringBuffer);
		AdditionalEquipment = stringBuffer;

		getline(is, stringBuffer);
		NumOfComputers = stoi(stringBuffer);
	}*/

	void Edit(LabRoom roomToEdit)
	{
		IRoom::Edit(roomToEdit);
		this->AdditionalEquipment = roomToEdit.AdditionalEquipment;
		this->NumOfComputers = roomToEdit.NumOfComputers;
	}

	void Serialize(ostream& os) const
	{
		IRoom::Serialize(os);
		os << AdditionalEquipment << endl
			<< NumOfComputers;
	}
};