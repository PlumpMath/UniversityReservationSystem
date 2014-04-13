#pragma once

#include "IController.h"
#include "Student.h"
#include "DataContext.h"

class StudentController : public IController<Student>
{
public:
	StudentController(DataContext & _context)
		: IController(_context) { }

	bool Add(Student& toAdd)
	{
		Context.Students.Add(toAdd, true);
		toAdd.Reservations.AddRange(toAdd.StudentGroup.Reservations);
		return true;
	}

	bool Edit(Student& toEdit)
	{
		this->Delete(toEdit);
		return this->Add(toEdit);
	}

	bool Delete(Student& toFind)
	{
		Student toDelete = Context.Students.Find(toFind);

		toDelete.StudentGroup.Students.Remove(toDelete);

		Context.Students.Delete(toDelete);
		return true;
	}
};