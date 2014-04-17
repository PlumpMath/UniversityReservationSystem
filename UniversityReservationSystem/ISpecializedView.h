#pragma once

template <class T>
class ISpecializedView
{
protected:
	T& Controller;
public:
	ISpecializedView(DataContext& _context) : Controller(*(new T(_context))) {}

	virtual ~ISpecializedView()
	{
		delete &Controller;
	}
};