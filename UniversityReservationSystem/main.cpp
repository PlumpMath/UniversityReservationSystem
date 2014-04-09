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
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

void main()
{
	{
		LabRoom room = LabRoom("nazwalab", 323, "none eq", 2);
		ExerciseRoom room2 = ExerciseRoom("nazwaEx", 3, 32, 23);
		Group group = Group("degree", 2012, 2);
		Student student1 = Student("imie1", "nazwisko1", group, 3, 2.3);
		Student student2 = Student("imie2", "nazwisko2", group, 6, 4.6);
		Teacher teacher = Teacher("pierwsze", "drugie", "mail", "3423423423", "tytul");

		Reservation res = Reservation("nazwa", time(0), time(0), teacher, room);
		res.BoundGroups.Add(group);
		group.Students.Add(student1);
		group.Students.Add(student2);

		DataContext context = DataContext("home");

		ReservationController reserv = ReservationController(context);
		reserv.Add(res);
		cout << "hehe";
	}
	_CrtDumpMemoryLeaks();

	cin;
}