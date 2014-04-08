#pragma once

#include "IController.h"
#include "Student.h"
#include "DataContext.h"

class StudentController : public IController
{
public:
	StudentController(DataContext & _context)
		: IController(_context) { }


};