#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "Reservation.h"

using namespace std;

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

	//
	// Constructor used during deserialization
	//
	Group(string _degreeCourse, int _year, int _groupNumber, int _id)
		: ISerializable(_id)
	{
		DegreeCourse = _degreeCourse;
		Year = _year;
		GroupNumber = _groupNumber;
	}

	static Group& Deserialize(ifstream& is, DataContext& context)
	{
		string stringBuffer;

		getline(is, stringBuffer);
		int id = stoi(stringBuffer);

		getline(is, stringBuffer);
		string degreeCourse = stringBuffer;

		getline(is, stringBuffer);
		int year = stoi(stringBuffer);

		getline(is, stringBuffer);
		int groupNumber = stoi(stringBuffer);

		return *(new Group(degreeCourse, year, groupNumber, id));
	}

	void Edit(Group roomToEdit)
	{
		this->DegreeCourse = roomToEdit.DegreeCourse;
		this->Year = roomToEdit.Year;
		this->GroupNumber = roomToEdit.GroupNumber;
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

	void RemoveReservation(Reservation &reservationToRemove)
	{
		Reservations.Remove(reservationToRemove);
		Students.RemoveReservation(reservationToRemove);
	}

	void Serialize(ostream& os)
	{
		ISerializable::Serialize(os);
		os << DegreeCourse << endl
			<< Year << endl
			<< GroupNumber;
	}
};