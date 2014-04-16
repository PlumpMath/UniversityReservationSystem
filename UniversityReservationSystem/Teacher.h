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
		: IPerson(_firstName, _lastName)
	{
		Email = _email;
		PhoneNumber = _phoneNumber;
		AcademicTitle = _academicTitle;
	}

	Teacher(string _firstName, string _lastName, string _email, string _phoneNumber, string _academicTitle, int _id)
		: IPerson(_firstName, _lastName, _id)
	{
		Email = _email;
		PhoneNumber = _phoneNumber;
		AcademicTitle = _academicTitle;
	}

	static Teacher& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		int id = stoi(stringBuffer);

		getline(is, stringBuffer);
		string firstName = stringBuffer;

		getline(is, stringBuffer);
		string lastName = stringBuffer;

		getline(is, stringBuffer);
		string email = stringBuffer;

		getline(is, stringBuffer);
		string phoneNumber = stringBuffer;

		getline(is, stringBuffer);
		string academicTitle = stringBuffer;

		return *(new Teacher(firstName, lastName, email, phoneNumber, academicTitle, id));
	}

	void Edit(Teacher& editedTeacher)
	{
		IPerson::Edit(editedTeacher);
		this->Email = editedTeacher.Email;
		this->PhoneNumber = editedTeacher.PhoneNumber;
		this->AcademicTitle = editedTeacher.AcademicTitle;
	}

	void Serialize(ostream& os)
	{
		IPerson::Serialize(os);
		os << Email << endl
			<< PhoneNumber << endl
			<< AcademicTitle;
	}
};