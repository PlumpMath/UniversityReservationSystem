#pragma once

#include "IController.h"
#include "Group.h"
#include "DataContext.h"

class GroupController : public IController
{
public:
	GroupController(DataContext & _context)
		: IController(_context) { }


};