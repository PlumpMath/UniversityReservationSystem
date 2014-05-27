#pragma once

#include <string>
#include <direct.h>

#define GROUPS_FILE "groups.txt"
#define TEACHERS_FILE "teachers.txt"
#define STUDENTS_FILE "students.txt"
#define ROOMS_FILE "rooms.txt"
#define RESERVATIONS_FILE "reservations.txt"

using namespace std;

class Group;
class Teacher;
class Student;

class DataContext
{
protected:
	string filePath;
public:
	TDataQueue<Group>		Groups;
	TDataQueue<Teacher>		Teachers;
	TDataQueue<Student>		Students;
	TDataQueue<IRoom>		Rooms;
	TDataQueue<Reservation>	Reservations;

	DataContext(string _filePath)
	{
		filePath = _filePath;
	}

	bool TrySaveChanges()
	{
		ofstream fileGroups			(filePath + "//" + GROUPS_FILE, ofstream::trunc);
		ofstream fileTeachers		(filePath + "//" + TEACHERS_FILE, ofstream::trunc);
		ofstream fileStudents		(filePath + "//" + STUDENTS_FILE, ofstream::trunc);
		ofstream fileRooms			(filePath + "//" + ROOMS_FILE, ofstream::trunc);
		ofstream fileReservations	(filePath + "//" + RESERVATIONS_FILE, ofstream::trunc);

		if (fileGroups			.is_open() &&
			fileTeachers		.is_open() &&
			fileStudents		.is_open() &&
			fileRooms			.is_open() &&
			fileReservations	.is_open())
		{
			fileGroups << Groups;
			fileGroups.close();

			fileTeachers << Teachers;
			fileTeachers.close();

			fileStudents << Students;
			fileStudents.close();

			fileRooms << Rooms;
			fileRooms.close();

			fileReservations << Reservations;
			fileReservations.close();

			return true;
		}
		return false;
	}

	bool TryLoadTheBase()
	{
		ifstream fileGroups(filePath + "//" + GROUPS_FILE);
		ifstream fileTeachers(filePath + "//" + TEACHERS_FILE);
		ifstream fileStudents(filePath + "//" + STUDENTS_FILE);
		ifstream fileRooms(filePath + "//" + ROOMS_FILE);
		ifstream fileReservations(filePath + "//" + RESERVATIONS_FILE);

		if (fileGroups			.is_open() &&
			fileTeachers		.is_open() &&
			fileStudents		.is_open() &&
			fileRooms			.is_open() &&
			fileReservations	.is_open())
		{
			Groups.Deserialize(fileGroups, *this);
			fileGroups.close();

			Teachers.Deserialize(fileTeachers, *this);
			fileTeachers.close();

			Students.Deserialize(fileStudents, *this);
			fileStudents.close();

			Rooms.Deserialize(fileRooms, *this);
			fileRooms.close();

			Reservations.Deserialize(fileReservations, *this);
			fileReservations.close();

			return true;
		}
		return false;
	}

	void Clear()
	{
		Students		.Clear();
		Groups			.Clear();
		Teachers		.Clear();
		Rooms			.Clear();
		Reservations    .Clear();
	}

	~DataContext()
	{
		Clear();
	}
};