#pragma once

#include "DataContext.h"
#include "Group.h"
#include "IPerson.h"
#include "TDataQueue.h"

using namespace std;

class Group;
class DataContext;

class Student : public IPerson
{
public:
	int PassedTerms;
	double AverageOfMarksOfLastTerm;
	Group* StudentGroup;

	Student(string _firstName, string _lastName, Group* _group, int _passedTerms, double _averageOfMarksOfLastTerm)
		: IPerson(_firstName, _lastName), StudentGroup(_group)
	{
		PassedTerms = _passedTerms;
		AverageOfMarksOfLastTerm = _averageOfMarksOfLastTerm;
	}

	//
	// Constructor used during deserialization
	//
	Student(string _firstName, string _lastName, Group* _group, int _passedTerms, double _averageOfMarksOfLastTerm, int _id)
		: IPerson(_firstName, _lastName, _id), StudentGroup(_group)
	{
		PassedTerms = _passedTerms;
		AverageOfMarksOfLastTerm = _averageOfMarksOfLastTerm;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		// Since groups have to check it
		return false;
	}

	static Student& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		int id = stoi(stringBuffer);

		getline(is, stringBuffer);
		string firstName = stringBuffer;

		getline(is, stringBuffer);
		string lastName = stringBuffer;

		getline(is, stringBuffer);
		int passedTerms = stoi(stringBuffer);

		getline(is, stringBuffer);
		double average = stod(stringBuffer);

		getline(is, stringBuffer);
		int groupId = stoi(stringBuffer);

		Group* group = &context.Groups.FindById(groupId);

		return *(new Student(firstName, lastName, group, passedTerms, average, id ));
	}

	virtual void Edit(Student& editedStudent)
	{
		IPerson::Edit(editedStudent);
		this->PassedTerms = editedStudent.PassedTerms;
		this->AverageOfMarksOfLastTerm = editedStudent.AverageOfMarksOfLastTerm;

		if (*StudentGroup != *editedStudent.StudentGroup)
		{
			this->Reservations.Clear(true);
			this->StudentGroup->Students.Remove(*this);
			this->StudentGroup = editedStudent.StudentGroup;
			this->StudentGroup->Students.Add(*this);
			this->Reservations.AddRange(this->StudentGroup->Reservations);
		}
	}

	virtual void Serialize(ostream& os)
	{
		IPerson::Serialize(os);
		os << PassedTerms << endl
			<< AverageOfMarksOfLastTerm << endl
			<< StudentGroup->Id;
	}
};