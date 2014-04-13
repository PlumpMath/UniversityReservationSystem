#pragma once

#include "IPerson.h"
#include <fstream>

using namespace std;

class Teacher : public IPerson
{
public:
	string Email;
	string PhoneNumber;
	string AcademicTitle;

	Teacher(string _firstName, string _lastName, string _email, string _phoneNumber, string _academicTitle)
		: IPerson(_firstName, _lastName, "Teacher")
	{
		Email = _email;
		PhoneNumber = _phoneNumber;
		AcademicTitle = _academicTitle;
	}

	Teacher(ifstream& is) : IPerson(is, "Teacher")
	{
		string stringBuffer;

		getline(is, stringBuffer);
		Email = stringBuffer;

		getline(is, stringBuffer);
		PhoneNumber = stringBuffer;

		getline(is, stringBuffer);
		AcademicTitle = stringBuffer;
	}

	void Edit(Teacher& editedTeacher)
	{
		IPerson::Edit(editedTeacher);
		this->Email = editedTeacher.Email;
		this->PhoneNumber = editedTeacher.PhoneNumber;
		this->AcademicTitle = editedTeacher.AcademicTitle;
	}

	void Serialize(ostream& os) const
	{
		IPerson::Serialize(os);
		os << Email << endl
			<< PhoneNumber << endl
			<< AcademicTitle;
	}
};