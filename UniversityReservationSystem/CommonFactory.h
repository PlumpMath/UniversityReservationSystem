#pragma once

using namespace std;

class Student;
class Teacher;
class Reservation;
class Group;
class LabRoom;
class ExerciseRoom;
class DataContext;

class CommonFactory
{
public:
	static ISerializable* NewObject(ifstream& is, DataContext& context)
	{
		return new ISerializable();
	}
};