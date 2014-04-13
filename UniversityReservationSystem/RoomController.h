#pragma once

#include "IController.h"
#include "IRoom.h"
#include "DataContext.h"

class RoomController : public IController<IRoom>
{
public:
	RoomController(DataContext & _context)
		: IController(_context) { }

	bool Add(IRoom& toAdd)
	{
		Context.Rooms.Add(toAdd, true);
		return true;
	}

	bool Edit(IRoom& copyOfRoomToModify)
	{
		IRoom toEdit = Context.Rooms.Find(copyOfRoomToModify);
		toEdit.Edit(copyOfRoomToModify);
	}

	bool Delete(IRoom& toFind)
	{
		IRoom toDelete = Context.Rooms.Find(toFind);

		for (int i = 0; i < toDelete.Reservations.Count(); i++)
		{
			toDelete.Reservations[i].BoundGroups.RemoveReservation(toDelete.Reservations[i]);
			toDelete.Reservations[i].BoundTeacher.RemoveReservation(toDelete.Reservations[i]);
			Context.Reservations.Delete(toDelete.Reservations[i]);
		}

		Context.Rooms.Delete(toDelete);
		return true;
	}
};