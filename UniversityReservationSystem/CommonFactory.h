#pragma once

#include "Group.h"
#include "TDataQueue.h"

using namespace std;

class DataContext;

class CommonFactory
{
private:
	string _type;
public:
	CommonFactory(string type)
	{
		_type = type;
	}

	ISerializable* TakeNewObject(
		ifstream& is,
		DataContext* context,
		string type)
	{
		return new Group("DFDF", 3, 3);
	}
};