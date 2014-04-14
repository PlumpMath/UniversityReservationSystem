#include "Student.h"
#include "Teacher.h"
#include "Reservation.h"
#include "Group.h"
#include "LabRoom.h"
#include "ExerciseRoom.h"
#include "GroupController.h"
#include "StudentController.h"
#include "TeacherController.h"
#include "RoomController.h"
#include "ReservationController.h"

using namespace std;

class MainPageView
{
private:
	DataContext& context;
public:
	MainPageView(DataContext& _context) : context(_context) { }

	void Test()
	{
		LabRoom * room = new LabRoom("n2azwalab", 323, "none eq", 2);
		Group * group = new Group("degree", 2012, 2);
		Student * student1 = new Student("imie1", "n1azwisko1", *group, 3, 2.3);
		Student * student2 = new Student("imie2", "n1azwisko2", *group, 6, 4.6);
		Teacher * teacher = new Teacher("pierwsze", "drugie", "mail", "3423423423", "tytul");
		Reservation * res = new Reservation("n3azwa", time(0), time(0), *teacher, *room);
		res->BoundGroups.Add(*group);

		GroupController groupCtrl(context);
		StudentController studentCtrl(context);
		TeacherController teacherCtrl(context);
		RoomController roomCtrl(context);
		ReservationController reservationCtrl(context);

		groupCtrl.Add(*group);
		studentCtrl.Add(*student1);
		studentCtrl.Add(*student2);
		teacherCtrl.Add(*teacher);
		roomCtrl.Add(*room);
		reservationCtrl.Add(*res);
	}
};