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
		return true;
	}

	bool Edit(Group& toEdit)
	{
		return true;
	}

	bool Delete(Group& toDelete)
	{
		return true;
	}
};