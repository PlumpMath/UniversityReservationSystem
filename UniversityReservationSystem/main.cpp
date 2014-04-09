#include <string>
#include <iostream>
#include "Student.h"
#include "Teacher.h"
#include "Reservation.h"
#include "Group.h"
#include "LabRoom.h"
#include "ExerciseRoom.h"
#include "DataContext.h"
#include "ReservationController.h"

using namespace std;

void main()
{
	LabRoom *room = new LabRoom("nazwalab", 323, "none eq", 2);
	ExerciseRoom *room2 = new ExerciseRoom("nazwaEx", 3, 32, 23);
	Group *group = new Group("degree", 2012, 2);
	Student *student1 = new Student("imie1", "nazwisko1", *group, 3, 2.3);
	Student *student2 = new Student("imie2", "nazwisko2", *group, 6, 4.6);
	Teacher *teacher = new Teacher("pierwsze", "drugie", "mail", "3423423423", "tytul");

	Reservation *res = new Reservation("nazwa", time(0), time(0), *teacher, *room);
	res->BoundGroups.Add(group);
	group->Students.Add(student1);
	group->Students.Add(student2);


	DataContext *context = new DataContext("home");
	ReservationController *reserv = new ReservationController(*context);
	context->Reservations.Add(res, true);
	context->SaveChanges();

	cin;
}