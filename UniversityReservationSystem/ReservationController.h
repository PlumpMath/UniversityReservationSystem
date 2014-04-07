#pragma once

#include "Reservation.h"
#include "DataContext.h"

class ReservationController
{
private:
	DataContext& Context;

public:
	ReservationController(DataContext & _context)
		: Context(_context) { }

	void AddReservation(Reservation& toAdd)
	{
		if (toAdd.BoundGroups.CheckCollisions(toAdd))
		{

		}

		toAdd.BoundTeacher.Reservations.Add(&toAdd);
		toAdd.Room.Reservations.Add(&toAdd);
		Context.Reservations.Add(&toAdd);
	}
};