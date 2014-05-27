#pragma once

#include "IController.h"
#include "Student.h"
#include "DataContext.h"

/* Class-controller - management over operations on students */

class StudentController : public IController<Student>
{
public:
	StudentController(DataContext & _context)
		: IController(_context, _context.Students) { }

	bool Add(Student& toAdd)
	{
		Context.Students.Add(toAdd, true);
		toAdd.StudentGroup->Students.Add(toAdd);
		toAdd.Reservations.AddRange(toAdd.StudentGroup->Reservations);
		return true;
	}

	bool Edit(Student& copyOfStudentToModify)
	{
		Student& toEdit = Context.Students.Find(copyOfStudentToModify);
		toEdit.Edit(copyOfStudentToModify);
		return true;
	}

	bool Delete(Student& toDelete)
	{
		toDelete.StudentGroup->Students.Remove(toDelete);

		Context.Students.Delete(toDelete);
		return true;
	}
};