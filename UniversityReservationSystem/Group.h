#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "Student.h"
#include "Reservation.h"
using namespace std;

class Reservation;
class Student;

class Group : public ISerializable
{
public:
	string DegreeCourse;
	int Year;
	int GroupNumber;
	TAntiCollisionQueue<Student> Students;
	TAntiCollisionQueue<Reservation> Reservations;

	Group(string _degreeCourse, int _year, int _groupNumber)
	{
		DegreeCourse = _degreeCourse;
		Year = _year;
		GroupNumber = _groupNumber;
	}

	Group(ifstream& is) : ISerializable(is)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		DegreeCourse = stringBuffer;

		getline(is, stringBuffer);
		Year = stoi(stringBuffer);

		getline(is, stringBuffer);
		GroupNumber = stoi(stringBuffer);
	}

	bool CheckCollisions(Reservation& reservation)
	{
		return Reservations.CheckCollisions(reservation);
	}

	void AddReservation(Reservation& reservation)
	{
		Reservations.Add(reservation);
		Students.AddReservation(reservation);
	}

	void Serialize(ostream& os) const
	{
		ISerializable::Serialize(os);
		os << DegreeCourse << endl
			<< Year << endl
			<< GroupNumber;
	}
};