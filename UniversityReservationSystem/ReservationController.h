#pragma once

#include "IController.h"
#include "Reservation.h"
#include "DataContext.h"

class ReservationController : public IController<Reservation>
{
public:
	ReservationController(DataContext & _context)
		: IController(_context, _context.Reservations) { }

	bool Add(Reservation& toAdd)
	{
		if (toAdd.BoundGroups .CheckCollisions(toAdd)) return false;
		if (toAdd.BoundTeacher.CheckCollisions(toAdd)) return false;
		if (toAdd.Room        .CheckCollisions(toAdd)) return false;

		toAdd.BoundGroups .AddReservation(toAdd);
		toAdd.BoundTeacher.AddReservation(toAdd);
		toAdd.Room        .AddReservation(toAdd);

		Context.Reservations.Add(toAdd, true);
		return true;
	}

	bool Edit(Reservation& copyOfReservationToModify)
	{
		Reservation toEdit = Context.Reservations.Find(copyOfReservationToModify);
		toEdit.Edit(copyOfReservationToModify);
		return true;
	}
	
	bool Delete(Reservation& toFind)
	{
		Reservation toDelete = Context.Reservations.Find(toFind);

		toDelete.BoundGroups .RemoveReservation(toDelete);
		toDelete.BoundTeacher.RemoveReservation(toDelete);
		toDelete.Room	     .RemoveReservation(toDelete);

		Context.Reservations.Delete(toDelete);
		return true;
	}
};