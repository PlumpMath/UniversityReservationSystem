#pragma once

#include "IController.h"
#include "IRoom.h"
#include "DataContext.h"

class RoomController : public IController<IRoom>
{
public:
	RoomController(DataContext & _context)
		: IController(_context, _context.Rooms) { }

	bool Add(IRoom& toAdd)
	{
		Context.Rooms.Add(toAdd, true);
		return true;
	}

	bool Edit(IRoom& copyOfRoomToModify)
	{
		IRoom& toEdit = Context.Rooms.Find(copyOfRoomToModify);

		if (dynamic_cast<LabRoom*>(&toEdit))
			((LabRoom*)&toEdit)->Edit(*((LabRoom*)&copyOfRoomToModify));
		else
			((ExerciseRoom*)&toEdit)->Edit(*((ExerciseRoom*)&copyOfRoomToModify));

		toEdit.Edit(copyOfRoomToModify);
		return true;
	}

	bool Delete(IRoom& toDelete)
	{
		for (unsigned int i = 0; i < toDelete.Reservations.Count(); i++)
		{
			toDelete.Reservations[i].BoundGroups.RemoveReservation(toDelete.Reservations[i]);
			toDelete.Reservations[i].BoundTeacher->RemoveReservation(toDelete.Reservations[i]);
			Context.Reservations.Delete(toDelete.Reservations[i]);
		}

		Context.Rooms.Delete(toDelete);
		return true;
	}
};