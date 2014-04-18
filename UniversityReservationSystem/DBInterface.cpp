#include "stdafx.h"
#include "DataContext.h"

#define _CRTDBG_MAP_ALLOC
#define API __declspec(dllexport)
using namespace std;

DataContext * Context;

GroupController			* groupCtrl;
StudentController		* studentCtrl;
TeacherController		* teacherCtrl;
RoomController			* roomCtrl;
ReservationController	* reservationCtrl;

extern "C"
{
	API bool LoadDB(const char* filePath)
	{
		Context = new DataContext(filePath);
		bool success = Context->TryLoadTheBase();

		groupCtrl		= new GroupController		(*Context);
		studentCtrl		= new StudentController		(*Context);
		teacherCtrl		= new TeacherController		(*Context);
		roomCtrl		= new RoomController		(*Context);
		reservationCtrl = new ReservationController	(*Context);

		return success;
	}

	API bool SaveDB(void)
	{
		return Context->TrySaveChanges();
	}

	API void FreeDB(void)
	{
		delete groupCtrl;
		delete studentCtrl;
		delete teacherCtrl;
		delete roomCtrl;
		delete reservationCtrl;

		delete Context;
	}
}