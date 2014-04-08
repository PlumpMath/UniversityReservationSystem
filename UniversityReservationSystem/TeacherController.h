#pragma once

#include "IController.h"
#include "Teacher.h"
#include "DataContext.h"

class TeacherController : public IController<Teacher>
{
public:
	TeacherController(DataContext & _context)
		: IController(_context) { }

	bool Add(Teacher& toAdd)
	{
		return true;
	}

	bool Edit(Teacher& toEdit)
	{
		return true;
	}

	bool Delete(Teacher& toDelete)
	{
		return true;
	}
};