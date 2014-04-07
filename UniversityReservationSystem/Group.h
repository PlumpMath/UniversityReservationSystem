#pragma once

#include "TAntiCollisionQueue.h"
#include "Student.h"
#include "Reservation.h"

using namespace std;

class Reservation;
class Student;

class Group
{
public:
	string DegreeCourse;
	int Year;
	int GroupNumber;
	TAntiCollisionQueue<Student> Students;
	TQueue<Reservation> Reservations;

	Group(string _degreeCourse, int _year, int _groupNumber)
	{
		DegreeCourse = _degreeCourse;
		Year = _year;
		GroupNumber = _groupNumber;
	}

	bool CheckCollisions(Reservation& reservation)
	{
		if (Students.CheckCollisions(reservation)) return true;

		return false;
	}

	void AddReservation(Reservation& reservation)
	{
		Reservations.Add(&reservation);
		Students.AddReservation(reservation);
	}
};