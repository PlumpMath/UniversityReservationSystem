#pragma once

#include "IController.h"
#include "IRoom.h"
#include "DataContext.h"

class RoomController : public IController
{
public:
	RoomController(DataContext & _context)
		: IController(_context) { }


};