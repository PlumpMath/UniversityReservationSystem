#pragma once

#include "ISerializable.h"
#include "TAntiCollisionQueue.h"
#include "Reservation.h"

using namespace std;

class Student;

class Group : public IReservable
{
public:
	string DegreeCourse;
	int Year;
	int GroupNumber;
	TAntiCollisionQueue<Student> Students;

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
		: IReservable(_id)
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

	void Edit(Group& groupToEdit)
	{
		this->DegreeCourse = groupToEdit.DegreeCourse;
		this->Year = groupToEdit.Year;
		this->GroupNumber = groupToEdit.GroupNumber;
	}

	virtual void AddReservation(Reservation& reservationToAdd)
	{
		IReservable::AddReservation(reservationToAdd);
		Students.AddReservation(reservationToAdd);
	}

	virtual void RemoveReservation(Reservation &reservationToRemove)
	{
		IReservable::RemoveReservation(reservationToRemove);
		Students.RemoveReservation(reservationToRemove);
	}

	virtual void Serialize(ostream& os)
	{
		IReservable::ISerializable::Serialize(os);
		os << DegreeCourse << endl
			<< Year << endl
			<< GroupNumber;
	}
};