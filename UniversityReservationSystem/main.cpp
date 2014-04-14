#include <string>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MainPageView.h"
#include "DataContext.h"

using namespace std;

int main()
{
	{
		DataContext context("home");
		MainPageView mainView(context);
		mainView.Test();
		context.SaveChanges();
	}

	// Odd brackets to see eventual memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}