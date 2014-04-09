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
		if (!Context.Groups.Contains(toAdd))
		{
			Context.Groups.Add(toAdd);
			return true;
		}
		return false;
	}

	bool Edit(Group& toEdit)
	{
		return true;
	}

	bool Delete(Group& toDelete)
	{
		Context.Groups.Remove(toDelete);
		//Context.People.DeleteRange(toDelete.Students);
		toDelete.Students.Clear();
		// TODO: FUCK THIS SHIT WITH STORING IDIOTIC GENERIC QUEUES

		delete &toDelete;
	}
};