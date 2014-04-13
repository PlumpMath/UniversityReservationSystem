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

	bool Edit(IRoom& toEdit)
	{
		this->Delete(toEdit);
		return this->Add(toEdit);
	}

	bool Delete(IRoom& toFind)
	{
		IRoom toDelete = Context.Rooms.Find(toFind);


		Context.Rooms.Delete(toDelete);
		return true;
	}
};