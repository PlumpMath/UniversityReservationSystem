#include <string>
#include <vector>
#include "Student.h"
using namespace std;

class Group
{
public:
	string DegreeCourse;
	int Year;
	int GroupNumber;
	vector<Student> Students;

	Group(string _degreeCourse, int _year, int _groupNumber)
	{
		DegreeCourse = _degreeCourse;
		Year = _year;
		GroupNumber = _groupNumber;
	}
};