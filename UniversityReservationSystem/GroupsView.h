#pragma once

#include "ISpecializedView.h"

class GroupController;

class GroupsView : public ISpecializedView<GroupController>
{
public:
	GroupsView(DataContext& _context) : ISpecializedView(_context) {}
};