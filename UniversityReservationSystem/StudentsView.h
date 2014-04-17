#pragma once

#include "ISpecializedView.h"

class StudentController;

class StudentsView : public ISpecializedView<StudentController>
{
public:
	StudentsView(DataContext& _context) : ISpecializedView(_context) {}


};