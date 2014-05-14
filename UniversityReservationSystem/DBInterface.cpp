#include "stdafx.h"
#include "DataContext.h"

#define _CRTDBG_MAP_ALLOC
#define API __declspec(dllexport)
#define uint unsigned int
#define strPtr const char *
using namespace std;

DataContext * Context;

GroupController			* groupCtrl;
StudentController		* studentCtrl;
TeacherController		* teacherCtrl;
RoomController			* roomCtrl;
ReservationController	* reservationCtrl;

extern "C"
{
	////////////////////////////////////
	//////// COMMON
	////////////////////////////////////

	API bool			LoadDB(strPtr filePath)
	{
		Context = new DataContext(filePath);
		bool success = Context->TryLoadTheBase();

		groupCtrl = new GroupController(*Context);
		studentCtrl = new StudentController(*Context);
		teacherCtrl = new TeacherController(*Context);
		roomCtrl = new RoomController(*Context);
		reservationCtrl = new ReservationController(*Context);

		return success;
	}
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

		_CrtDumpMemoryLeaks();
	}

	API int				GetID(ISerializable * iserializablePtr)
	{
		return iserializablePtr->Id;
	}
	API Group *			GetGroupByIndex(uint groupIndex)
	{
		return &(groupCtrl->List[groupIndex]);
	}
	API Student *		GetStudentByIndex(uint studentIndex)
	{
		return &(studentCtrl->List[studentIndex]);
	}
	API Teacher *		GetTeacherByIndex(uint teacherIndex)
	{
		return &(teacherCtrl->List[teacherIndex]);
	}
	API IRoom *			GetRoomByIndex(uint roomIndex)
	{
		return &(roomCtrl->List[roomIndex]);
	}
	API Reservation *	GetReservationByIndex(uint reservationIndex)
	{
		return &(reservationCtrl->List[reservationIndex]);
	}

	API uint			GetGroupsCount()
	{
		return groupCtrl->List.Count();
	}
	API uint			GetStudentsCount()
	{
		return studentCtrl->List.Count();
	}
	API uint			GetTeachersCount()
	{
		return teacherCtrl->List.Count();
	}
	API uint			GetRoomsCount()
	{
		return roomCtrl->List.Count();
	}
	API uint			GetReservationsCount()
	{
		return reservationCtrl->List.Count();
	}

	////////////////////////////////////
	//////// GROUPS
	////////////////////////////////////

	API strPtr			GetGroupDegreeCourse(Group * groupPtr)
	{
		return groupPtr->DegreeCourse.c_str();
	}
	API int				GetGroupYear(Group * groupPtr)
	{
		return groupPtr->Year;
	}
	API int				GetGroupNumber(Group * groupPtr)
	{
		return groupPtr->GroupNumber;
	}
	API Group *			CreateNewGroup(strPtr degreeCourse, int year, int groupNumber)
	{
		Group * group = new Group(degreeCourse, year, groupNumber);
		groupCtrl->Add(*group);

		return group;
	}
	API uint			GetGroupStudentsCount(Group * groupPtr)
	{
		return groupPtr->Students.Count();
	}
	API void			EditGroup(Group * groupPtr, strPtr degreeCourse, int year, int groupNumber)
	{
		Group copy(*groupPtr);

		copy.DegreeCourse = degreeCourse;
		copy.Year = year;
		copy.GroupNumber = groupNumber;

		groupCtrl->Edit(copy);
	}
	API void			DeleteGroup(Group * groupPtr)
	{
		groupCtrl->Delete(*groupPtr);
	}

	////////////////////////////////////
	//////// PEOPLE
	////////////////////////////////////

	API strPtr			GetPersonFirstName(IPerson * personPtr)
	{
		return personPtr->FirstName.c_str();
	}
	API strPtr			GetPersonLastName(IPerson * personPtr)
	{
		return personPtr->LastName.c_str();
	}

	////////////////////////////////////
	//////// STUDENTS
	////////////////////////////////////

	API Group *			GetStudentGroup(Student * studentPtr)
	{
		return studentPtr->StudentGroup;
	}
	API int				GetStudentPassedTerms(Student * studentPtr)
	{
		return studentPtr->PassedTerms;
	}
	API double			GetStudentAvgOfMarks(Student * studentPtr)
	{
		return studentPtr->AverageOfMarksOfLastTerm;
	}
	API Student *		CreateNewStudent(strPtr firstName, strPtr lastName, Group * groupPtr, int passedTerms, double avgOfMarks)
	{
		Student * student = new Student(firstName, lastName, groupPtr, passedTerms, avgOfMarks);
		studentCtrl->Add(*student);

		return student;
	}
	API void			EditStudent(Student * studentPtr, strPtr firstName, strPtr lastName, Group * groupPtr, int passedTerms, double avgOfMarks)
	{
		Student copy(*studentPtr);

		copy.FirstName = firstName;
		copy.LastName = lastName;
		copy.StudentGroup = groupPtr;
		copy.PassedTerms = passedTerms;
		copy.AverageOfMarksOfLastTerm = avgOfMarks;

		studentCtrl->Edit(copy);
	}
	API void			DeleteStudent(Student * studentPtr)
	{
		studentCtrl->Delete(*studentPtr);
	}

	////////////////////////////////////
	//////// TEACHERS
	////////////////////////////////////

	API strPtr			GetTeacherEmail(Teacher * teacherPtr)
	{
		return teacherPtr->Email.c_str();
	}
	API strPtr			GetTeacherPhoneNumber(Teacher * teacherPtr)
	{
		return teacherPtr->PhoneNumber.c_str();
	}
	API strPtr			GetTeacherAcademicTitle(Teacher * teacherPtr)
	{
		return teacherPtr->AcademicTitle.c_str();
	}
	API Teacher *		CreateNewTeacher(strPtr firstName, strPtr lastName, strPtr email, strPtr phoneNumber, strPtr academicTitle)
	{
		Teacher * teacher = new Teacher(firstName, lastName, email, phoneNumber, academicTitle);
		teacherCtrl->Add(*teacher);

		return teacher;
	}
	API void			EditTeacher(Teacher * teacherPtr, strPtr academicTitle, strPtr firstName, strPtr lastName, strPtr phoneNumber, strPtr email)
	{
		Teacher copy(*teacherPtr);

		copy.FirstName = firstName;
		copy.LastName = lastName;
		copy.AcademicTitle = academicTitle;
		copy.PhoneNumber = phoneNumber;
		copy.Email = email;

		teacherCtrl->Edit(copy);
	}
	API void			DeleteTeacher(Teacher * teacherPtr)
	{
		teacherCtrl->Delete(*teacherPtr);
	}

	////////////////////////////////////
	//////// ROOMS
	////////////////////////////////////

	API strPtr			GetRoomName(IRoom * roomPtr)
	{
		return roomPtr->Name.c_str();
	}
	API int				GetRoomCapacity(IRoom * roomPtr)
	{
		return roomPtr->Capacity;
	}

	////////////////////////////////////
	//////// RESERVATIONS
	////////////////////////////////////

	API strPtr			GetReservationName(Reservation * reservationPtr)
	{
		return reservationPtr->Name.c_str();
	}
	API long int		GetReservationDateOfStart(Reservation * reservationPtr)
	{
		return reservationPtr->DateOfStart;
	}
	API long int		GetReservationDateOfEnd(Reservation * reservationPtr)
	{
		return reservationPtr->DateOfEnd;
	}
	API Teacher *		GetReservationTeacher(Reservation * reservationPtr)
	{
		return &(reservationPtr->BoundTeacher);
	}
	API IRoom *			GetReservationRoom(Reservation * reservationPtr)
	{
		return &(reservationPtr->Room);
	}
	API uint			GetReservationGroupsCount(Reservation * reservationPtr)
	{
		return reservationPtr->BoundGroups.Count();
	}
	API Reservation *	CreateNewReservation(strPtr name, long int dateOfStart, long int dateOfEnd, Teacher * teacher, IRoom * room)
	{
		Reservation * reservation = new Reservation(name, dateOfStart, dateOfEnd, *teacher, *room);
		reservationCtrl->Add(*reservation);

		return reservation;
	}
}