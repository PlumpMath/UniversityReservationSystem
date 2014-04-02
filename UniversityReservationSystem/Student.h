#include "IPerson.h"

class Student : public IPerson
{
public:
	int PassedTerms;
	double AverageOfMarksOfLastTerm;

	Student(string _firstName, string _lastName, int _passedTerms, double _averageOfMarksOfLastTerm)
		: IPerson(_firstName, _lastName)
	{
		PassedTerms = _passedTerms;
		AverageOfMarksOfLastTerm = _averageOfMarksOfLastTerm;
	}
};