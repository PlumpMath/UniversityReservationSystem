#pragma once

#include "ISpecializedView.h"

class ReservationController;

class ReservationsView : public ISpecializedView<ReservationController>
{
public:
	ReservationsView(DataContext& _context) : ISpecializedView(_context)
	{
		cout << Controller.List[0].Name;
	}
};