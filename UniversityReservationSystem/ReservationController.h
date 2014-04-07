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

	bool AddReservation(Reservation& toAdd)
	{
		if (toAdd.BoundGroups .CheckCollisions(toAdd)) return false;
		if (toAdd.BoundTeacher.CheckCollisions(toAdd)) return false;
		if (toAdd.Room        .CheckCollisions(toAdd)) return false;

		toAdd.BoundGroups .AddReservation(toAdd);
		toAdd.BoundTeacher.AddReservation(toAdd);
		toAdd.Room        .AddReservation(toAdd);

		Context.Reservations.Add(&toAdd);
	}
};