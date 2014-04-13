#pragma once

#include "IController.h"
#include "Group.h"
#include "DataContext.h"

class GroupController : public IController<Group>
{
public:
	GroupController(DataContext & _context)
		: IController(_context) { }

	bool Add(Group& toAdd)
	{
		Context.Groups.Add(toAdd, true);
		return true;
	}

	bool Edit(Group& toEdit)
	{
		this->Delete(toEdit);
		return this->Add(toEdit);
	}

	bool Delete(Group& toFind)
	{
		Group toDelete = Context.Groups.Find(toFind);

		for (int i = 0; i < toDelete.Reservations.Count(); i++)
		{
			toDelete.Reservations[i].BoundTeacher.RemoveReservation(toDelete.Reservations[i]);
			toDelete.Reservations[i].Room.RemoveReservation(toDelete.Reservations[i]);
			Context.Reservations.Delete(toDelete.Reservations[i]);
		}

		for (int i = 0; i < toDelete.Students.Count(); i++)
		{
			Context.Students.Remove(toDelete.Students[i]);
		}

		Context.Groups.Delete(toDelete);
		return true;
	}
};