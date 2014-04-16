#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include <crtdbg.h>
#include "MainPageView.h"
#include "DataContext.h"

#define _CRTDBG_MAP_ALLOC
using namespace std;

int main()
{
	{
		DataContext context("home");
		MainPageView mainView(context);
		mainView.Test();
		//context.SaveChanges();
	}

	// Odd brackets to see eventual memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}