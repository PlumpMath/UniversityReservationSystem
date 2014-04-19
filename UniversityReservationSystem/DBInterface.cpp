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

	API int GetID(ISerializable * iserializablePtr)
	{
		if (iserializablePtr != NULL)
		{
			return iserializablePtr->Id;
		}
	}

	////////////////////////////////////
	//////// GROUPS
	////////////////////////////////////

	API const char * GetGroupDegreeCourse(Group * groupPtr)
	{
		if (groupPtr != NULL)
		{
			return groupPtr->DegreeCourse.c_str();
		}
	}

	API int GetGroupYear(Group * groupPtr)
	{
		if (groupPtr != NULL)
		{
			return groupPtr->Year;
		}
	}

	API int GetGroupNumber(Group * groupPtr)
	{
		if (groupPtr != NULL)
		{
			return groupPtr->GroupNumber;
		}
	}

	API Group * CreateNewGroup(const char * degreeCourse, int year, int groupNumber)
	{
		Group * group = new Group(degreeCourse, year, groupNumber);
		groupCtrl->Add(*group);

		return group;
	}

	////////////////////////////////////
	//////// STUDENTS
	////////////////////////////////////

	API Group * GetStudentGroup(Student * studentPtr)
	{
		return &(studentPtr->StudentGroup);
	}

	API int GetStudentPassedTerms(Student * studentPtr)
	{
		return studentPtr->PassedTerms;
	}

	API double GetStudentAvgOfMarks(Student * studentPtr)
	{
		return studentPtr->AverageOfMarksOfLastTerm;
	}

	API Student * CreateNewStudent(const char * firstName, const char * lastName,
		Group * group, int passedTerms, double avgOfMarks)
	{
		Student * student = new Student(firstName, lastName, *group, passedTerms, avgOfMarks);
		studentCtrl->Add(*student);

		return student;
	}

	API const char * GetStudentFirstName(Student * studentPtr)
	{
		if (studentPtr != NULL)
		{
			return studentPtr->FirstName.c_str();
		}
	}

	API const char * GetStudentLastName(Student * studentPtr)
	{
		if (studentPtr != NULL)
		{
			return studentPtr->LastName.c_str();
		}
	}
}