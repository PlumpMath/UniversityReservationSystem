#pragma once

#include "TQueue.h"
#include "Student.h"
#include "Reservation.h"

using namespace std;

class Student;
class Reservation;
class Group
{
public:
	string DegreeCourse;
	int Year;
	int GroupNumber;
	TQueue<Student> Students;
	TQueue<Reservation> Reservations;

	Group(string _degreeCourse, int _year, int _groupNumber)
	{
		DegreeCourse = _degreeCourse;
		Year = _year;
		GroupNumber = _groupNumber;
	}

	bool CheckCollisions(Reservation& resToCheck)
	{
		return true;
	}
};