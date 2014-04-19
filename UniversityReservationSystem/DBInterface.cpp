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
		reservationCtrl	= new ReservationController	(*Context);

		return success;
	}

	////////////////////////////////////
	//////// COMMON
	////////////////////////////////////

	API bool			SaveDB(void)
	{
		return Context->TrySaveChanges();
	}
	API void			FreeDB(void)
	{
		delete groupCtrl;
		delete studentCtrl;
		delete teacherCtrl;
		delete roomCtrl;
		delete reservationCtrl;

		delete Context;
	}

	API int				GetID(ISerializable * iserializablePtr)
	{
		if (iserializablePtr == NULL) throw 1;
		return iserializablePtr->Id;
	}
	API Group *			GetGroupByIndex(unsigned int groupIndex)
	{
		return &(groupCtrl->List[groupIndex]);
	}
	API Student *		GetStudentByIndex(unsigned int studentIndex)
	{
		return &(studentCtrl->List[studentIndex]);
	}
	API Teacher *		GetTeacherByIndex(unsigned int teacherIndex)
	{
		return &(teacherCtrl->List[teacherIndex]);
	}
	API IRoom *			GetRoomByIndex(unsigned int roomIndex)
	{
		return &(roomCtrl->List[roomIndex]);
	}
	API Reservation *	GetReservationByIndex(unsigned int reservationIndex)
	{
		return &(reservationCtrl->List[reservationIndex]);
	}

	API unsigned int	GetGroupsCount()
	{
		return groupCtrl->List.Count();
	}
	API unsigned int	GetStudentsCount()
	{
		return studentCtrl->List.Count();
	}
	API unsigned int	GetTeachersCount()
	{
		return teacherCtrl->List.Count();
	}
	API unsigned int	GetRoomsCount()
	{
		return roomCtrl->List.Count();
	}
	API unsigned int	GetReservationsCount()
	{
		return reservationCtrl->List.Count();
	}

	////////////////////////////////////
	//////// GROUPS
	////////////////////////////////////

	API const char *	GetGroupDegreeCourse(Group * groupPtr)
	{
		if (groupPtr == NULL) throw 1;
		return groupPtr->DegreeCourse.c_str();
	}
	API int				GetGroupYear(Group * groupPtr)
	{
		if (groupPtr == NULL) throw 1;
		return groupPtr->Year;
	}
	API int				GetGroupNumber(Group * groupPtr)
	{
		if (groupPtr == NULL) throw 1;
		return groupPtr->GroupNumber;
	}
	API Group *			CreateNewGroup(const char * degreeCourse, int year, int groupNumber)
	{
		Group * group = new Group(degreeCourse, year, groupNumber);
		groupCtrl->Add(*group);

		return group;
	}

	////////////////////////////////////
	//////// STUDENTS
	////////////////////////////////////

	API Group *			GetStudentGroup(Student * studentPtr)
	{
		if (studentPtr == NULL) throw 1;
		return &(studentPtr->StudentGroup);
	}
	API int				GetStudentPassedTerms(Student * studentPtr)
	{
		if (studentPtr == NULL) throw 1;
		return studentPtr->PassedTerms;
	}
	API double			GetStudentAvgOfMarks(Student * studentPtr)
	{
		if (studentPtr == NULL) throw 1;
		return studentPtr->AverageOfMarksOfLastTerm;
	}
	API Student *		CreateNewStudent(const char * firstName, const char * lastName, Group * groupPtr, int passedTerms, double avgOfMarks)
	{
		if (groupPtr == NULL) throw 1;

		Student * student = new Student(firstName, lastName, *groupPtr, passedTerms, avgOfMarks);
		studentCtrl->Add(*student);

		return student;
	}
	API const char *	GetStudentFirstName(Student * studentPtr)
	{
		if(studentPtr == NULL) throw 1;
		return studentPtr->FirstName.c_str();
	}
	API const char *	GetStudentLastName(Student * studentPtr)
	{
		if (studentPtr == NULL) throw 1;
		return studentPtr->LastName.c_str();
	}
}