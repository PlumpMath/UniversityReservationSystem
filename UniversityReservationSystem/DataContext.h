#pragma once

#include "TDataQueue.h"
#include "Reservation.h"
#include "Group.h"
#include "Teacher.h"
#include "Student.h"
#include "IRoom.h"
#include <fstream>

#define GROUPS_FILE "groups.txt"
#define TEACHERS_FILE "teachers.txt"
#define STUDENTS_FILE "students.txt"
#define ROOMS_FILE "rooms.txt"
#define RESERVATIONS_FILE "reservations.txt"

using namespace std;

class DataContext
{
protected:
	string filePath;
public:
	TDataQueue<Group> Groups;
	TDataQueue<Teacher> Teachers;
	TDataQueue<Student> Students;
	TDataQueue<IRoom> Rooms;
	TDataQueue<Reservation> Reservations;

	DataContext(string _filePath)
	{
		filePath = _filePath;
		TryLoadTheBase();
	}

	void SaveChanges()
	{
		ofstream fileGroups(filePath + "//" + GROUPS_FILE, ofstream::trunc);
		ofstream fileTeachers(filePath + "//" + TEACHERS_FILE, ofstream::trunc);
		ofstream fileStudents(filePath + "//" + STUDENTS_FILE, ofstream::trunc);
		ofstream fileRooms(filePath + "//" + ROOMS_FILE, ofstream::trunc);
		ofstream fileReservations(filePath + "//" + RESERVATIONS_FILE, ofstream::trunc);

		fileGroups.clear();
		fileGroups << Groups;
		fileGroups.close();

		fileTeachers.clear();
		fileTeachers << Teachers;
		fileTeachers.close();

		fileStudents.clear();
		fileStudents << Students;
		fileStudents.close();

		fileRooms.clear();
		fileRooms << Rooms;
		fileRooms.close();

		fileReservations.clear();
		fileReservations << Reservations;
		fileReservations.close();
	}

	void TryLoadTheBase()
	{
		ifstream fileGroups(filePath + "//" + GROUPS_FILE);
		ifstream fileTeachers(filePath + "//" + TEACHERS_FILE);
		ifstream fileStudents(filePath + "//" + STUDENTS_FILE);
		ifstream fileRooms(filePath + "//" + ROOMS_FILE);
		ifstream fileReservations(filePath + "//" + RESERVATIONS_FILE);

		fileGroups >> Groups;
		fileGroups.close();

		fileTeachers >> Teachers;
		fileTeachers.close();

		fileStudents >> Students;
		fileStudents.close();

		fileRooms >> Rooms;
		fileRooms.close();

		fileReservations >> Reservations;
		fileReservations.close();
	}

	void Clear()
	{
		Groups.Clear();
		Teachers.Clear();
		Students.Clear();
		Rooms.Clear();
		Reservations.Clear();
	}
};