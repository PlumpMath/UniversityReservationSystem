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
		return true;
	}

	bool Edit(IRoom& toEdit)
	{
		return true;
	}

	bool Delete(IRoom& toDelete)
	{
		return true;
	}
};