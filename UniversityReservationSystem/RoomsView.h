#pragma once

#include "ISpecializedView.h"

class RoomController;

class RoomsView : public ISpecializedView<RoomController>
{
public:
	RoomsView(DataContext& _context) : ISpecializedView(_context) {}


};