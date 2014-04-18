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
		DataContext * context = new DataContext(filePath);
		bool success = context->TryLoadTheBase();

		groupCtrl		= new GroupController		(*context);
		studentCtrl		= new StudentController		(*context);
		teacherCtrl		= new TeacherController		(*context);
		roomCtrl		= new RoomController		(*context);
		reservationCtrl = new ReservationController	(*context);

		return success;
	}

	API bool SaveDB()
	{
		return Context->TrySaveChanges();
	}

	API void FreeDB()
	{
		delete groupCtrl;
		delete studentCtrl;
		delete teacherCtrl;
		delete roomCtrl;
		delete reservationCtrl;

		delete Context;
	}
}