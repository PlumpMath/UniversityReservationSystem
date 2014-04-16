#pragma once

#include "IRoom.h"
#include <fstream>

using namespace std;

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

	LabRoom(string _name, int _capacity, string _additionalEquipment, int _numOfComputers, int _id)
		: IRoom(_name, "Lab", _capacity, _id)
	{
		AdditionalEquipment = _additionalEquipment;
		NumOfComputers = _numOfComputers;
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
		string addEquipment = stringBuffer;

		getline(is, stringBuffer);
		int numComputers = stoi(stringBuffer);

		return *(new LabRoom(name, capacity, addEquipment, numComputers, id));
	}

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