#pragma once

#include "IController.h"
#include "Teacher.h"
#include "DataContext.h"

/* Class-controller - management over operations on teachers */

class TeacherController : public IController<Teacher>
{
public:
	TeacherController(DataContext & _context)
		: IController(_context, _context.Teachers) { }

	bool Add(Teacher& toAdd)
	{
		Context.Teachers.Add(toAdd, true);
		return true;
	}

	bool Edit(Teacher& copyOfTeacherToModify)
	{
		Teacher& toEdit = Context.Teachers.Find(copyOfTeacherToModify);
		toEdit.Edit(copyOfTeacherToModify);
		return true;
	}

	bool Delete(Teacher& toDelete)
	{
		for (unsigned int i = 0; i < toDelete.Reservations.Count(); i++)
		{
			toDelete.Reservations[i].BoundGroups.RemoveReservation(toDelete.Reservations[i]);
			toDelete.Reservations[i].Room->RemoveReservation(toDelete.Reservations[i]);
			Context.Reservations.Delete(toDelete.Reservations[i]);
		}

		Context.Teachers.Delete(toDelete);
		return true;
	}
};