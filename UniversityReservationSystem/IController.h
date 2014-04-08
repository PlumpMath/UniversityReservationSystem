#pragma once

#include "DataContext.h"

class IController
{
protected:
	DataContext& Context;

public:
	IController(DataContext & _context)
		: Context(_context) { }

};