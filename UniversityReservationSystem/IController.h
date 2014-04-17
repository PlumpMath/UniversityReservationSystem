#pragma once

template <class T>
class TDataQueue;
class DataContext;

template <class T>
class IController
{
protected:
	DataContext& Context;
public:
	TDataQueue<T>& List;

	IController(DataContext & _context, TDataQueue<T>& _queue)
		: Context(_context), List(_queue) {}

	virtual bool Add(T& toAdd) = 0;
	virtual bool Edit(T& toEdit) = 0;
	virtual bool Delete(T& toDelete) = 0;

	virtual ~IController() { }
};