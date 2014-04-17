#pragma once

#include "ISpecializedView.h"

class TeacherController;

class TeachersView : public ISpecializedView<TeacherController>
{
public:
	TeachersView(DataContext& _context) : ISpecializedView(_context) {}


};