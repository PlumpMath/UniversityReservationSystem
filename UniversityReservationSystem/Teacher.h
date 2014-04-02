#pragma once

#include "IPerson.h"

class Teacher : public IPerson
{
public:
	string Email;
	string PhoneNumber;
	string AcademicTitle;

	Teacher(string _firstName, string _lastName, string _email, string _phoneNumber, string _academicTitle)
		: IPerson(_firstName, _lastName)
	{
		Email = _email;
		PhoneNumber = _phoneNumber;
		AcademicTitle = _academicTitle;
	}
};