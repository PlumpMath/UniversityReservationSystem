#pragma once

#include "DataContext.h"

template <class T>
class IController
{
protected:
	DataContext& Context;

public:
	IController(DataContext & _context)
		: Context(_context) { }

	virtual bool Add(T& toAdd) = 0;
	virtual bool Edit(T& toEdit) = 0;
	virtual bool Delete(T& toDelete) = 0;

	virtual ~IController() { }
};