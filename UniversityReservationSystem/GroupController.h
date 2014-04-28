#pragma once

#include "IController.h"
#include "Group.h"
#include "DataContext.h"

class GroupController : public IController<Group>
{
public:
	GroupController(DataContext & _context)
		: IController(_context, _context.Groups) { }

	bool Add(Group& toAdd)
	{
		Context.Groups.Add(toAdd, true);
		return true;
	}

	bool Edit(Group& copyOfGroupToEdit)
	{
		Group& toEdit = Context.Groups.Find(copyOfGroupToEdit);
		toEdit.Edit(copyOfGroupToEdit);
		return true;
	}

	bool Delete(Group& toDelete)
	{
		for (unsigned int i = 0; i < toDelete.Reservations.Count(); i++)
		{
			toDelete.Reservations[i].BoundTeacher.RemoveReservation(toDelete.Reservations[i]);
			toDelete.Reservations[i].Room.RemoveReservation(toDelete.Reservations[i]);
			Context.Reservations.Delete(toDelete.Reservations[i]);
		}

		for (unsigned int i = 0; i < toDelete.Students.Count(); i++)
		{
			Context.Students.Remove(toDelete.Students[i]);
		}

		Context.Groups.Delete(toDelete);
		return true;
	}
};