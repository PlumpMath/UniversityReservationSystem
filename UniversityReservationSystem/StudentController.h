#pragma once

#include "IController.h"
#include "Student.h"
#include "DataContext.h"

class StudentController : public IController<Student>
{
public:
	StudentController(DataContext & _context)
		: IController(_context) { }

	bool Add(Student& toAdd)
	{
		return true;
	}

	bool Edit(Student& toEdit)
	{
		return true;
	}

	bool Delete(Student& toDelete)
	{
		return true;
	}
};