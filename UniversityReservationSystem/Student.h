#pragma once
#include "Group.h"
#include "IPerson.h"
#include <fstream>

using namespace std;
class Group;

class Student : public IPerson
{
public:
	int PassedTerms;
	double AverageOfMarksOfLastTerm;
	Group& StudentGroup;

	Student(string _firstName, string _lastName, Group& _group, int _passedTerms, double _averageOfMarksOfLastTerm)
		: IPerson(_firstName, _lastName, "Student"), StudentGroup(_group)
	{
		PassedTerms = _passedTerms;
		AverageOfMarksOfLastTerm = _averageOfMarksOfLastTerm;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		// Since groups have to check it
		return false;
	}

	Student(ifstream& is, Group& _group) : IPerson(is, "Student"), StudentGroup(_group)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		PassedTerms = stoi(stringBuffer);

		getline(is, stringBuffer);
		AverageOfMarksOfLastTerm = stod(stringBuffer);
	}

	void Serialize(ostream& os) const
	{
		IPerson::Serialize(os);
		os << PassedTerms << endl
			<< AverageOfMarksOfLastTerm << endl
			<< StudentGroup.Id;
	}
};