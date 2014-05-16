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
		toAdd.BoundGroups  .AddReservation(toAdd);
		toAdd.BoundTeacher->AddReservation(toAdd);
		toAdd.Room        ->AddReservation(toAdd);

		Context.Reservations.Add(toAdd, true);
		return true;
	}

	bool Edit(Reservation& copyOfReservationToModify)
	{
		bool collisionsDetected = false;

		Reservation& toEdit = Context.Reservations.Find(copyOfReservationToModify);

		toEdit.BoundGroups.RemoveReservation(toEdit);
		toEdit.BoundTeacher->RemoveReservation(toEdit);
		toEdit.Room->RemoveReservation(toEdit);

		if ((!copyOfReservationToModify.BoundGroups.CheckCollisions(copyOfReservationToModify))
			|| (!copyOfReservationToModify.BoundTeacher->CheckCollisions(copyOfReservationToModify))
			|| (!copyOfReservationToModify.Room->CheckCollisions(copyOfReservationToModify)))
		{
			toEdit.BoundGroups.AddReservation(toEdit);
			toEdit.BoundTeacher->AddReservation(toEdit);
			toEdit.Room->AddReservation(toEdit);
			return false;
		}

		toEdit.BoundGroups = copyOfReservationToModify.BoundGroups;
		toEdit.BoundTeacher = copyOfReservationToModify.BoundTeacher;
		toEdit.Room = copyOfReservationToModify.Room;
		toEdit.DateOfEnd = copyOfReservationToModify.DateOfEnd;
		toEdit.DateOfStart = copyOfReservationToModify.DateOfStart;
		toEdit.Edit(copyOfReservationToModify);

		toEdit.BoundGroups.AddReservation(toEdit);
		toEdit.BoundTeacher->AddReservation(toEdit);
		toEdit.Room->AddReservation(toEdit);

		return true;
	}
	
	bool CheckCollisions(Reservation& toCheck)
	{
		if (!toCheck.BoundGroups.CheckCollisions(toCheck)) return false;
		if (!toCheck.BoundTeacher->CheckCollisions(toCheck)) return false;
		if (!toCheck.Room->CheckCollisions(toCheck)) return false;

		return true;
	}

	bool Delete(Reservation& toDelete)
	{
		toDelete.BoundGroups  .RemoveReservation(toDelete);
		toDelete.BoundTeacher->RemoveReservation(toDelete);
		toDelete.Room	     ->RemoveReservation(toDelete);

		Context.Reservations.Delete(toDelete);
		return true;
	}
};