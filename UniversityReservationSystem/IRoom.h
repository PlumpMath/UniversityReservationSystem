#include <vector>
#include <string>
#include "Reservation.h"

class IRoom
{
public:
	string Name;
	int Capacity;
	vector<Reservation> Reservations;

	IRoom(string _name, int _capacity)
	{
		Name = _name;
		Capacity = _capacity;
	}

	virtual ~IRoom() = 0;
};

IRoom::~IRoom() { }