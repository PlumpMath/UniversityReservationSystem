#pragma once

#include "IPerson.h"

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

	void Serialize(ostream& os) const
	{
		IPerson::Serialize(os);
		os << Email << endl 
			<< PhoneNumber << endl
			<< AcademicTitle << endl;
	}
};