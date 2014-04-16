#pragma once

#include "IController.h"

using namespace std;

template <class T>
class ControllerFactory
{
public:
	static IController<T>& CreateController(DataContext& context, string type)
	{
		if (type == "class Group")
		{
			return *(dynamic_cast<IController<T>*>(new GroupController(context)));
		}
		else if (type == "class Teacher")
		{
			return *(dynamic_cast<IController<T>*>(new TeacherController(context)));
		}
		else if (type == "class IRoom")
		{
			return *(dynamic_cast<IController<T>*>(new RoomController(context)));
		}
		else if (type == "class Student")
		{
			return *(dynamic_cast<IController<T>*>(new StudentController(context)));
		}
		else if (type == "class Reservation")
		{
			return *(dynamic_cast<IController<T>*>(new ReservationController(context)));
		}
		throw 1;
	}
};