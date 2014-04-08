#pragma once

#include "IController.h"
#include "Teacher.h"
#include "DataContext.h"

class TeacherController : public IController
{
public:
	TeacherController(DataContext & _context)
		: IController(_context) { }


};