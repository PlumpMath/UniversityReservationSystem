#pragma once
#include "Group.h"
#include "IPerson.h"


class Group;
class Student : public IPerson
{
public:
	int PassedTerms;
	double AverageOfMarksOfLastTerm;
	Group& StudentGroup;

	Student(string _firstName, string _lastName, Group& _group, int _passedTerms, double _averageOfMarksOfLastTerm)
		: IPerson(_firstName, _lastName), StudentGroup(_group)
	{
		PassedTerms = _passedTerms;
		AverageOfMarksOfLastTerm = _averageOfMarksOfLastTerm;
	}
};