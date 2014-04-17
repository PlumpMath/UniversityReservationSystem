#include "stdafx.h"
#include "DataContext.h"
#include "MainPageView.h"

#define _CRTDBG_MAP_ALLOC
using namespace std;

int main()
{
	{
		DataContext context("home");
		MainPageView mainView(context);
		//mainView.Test();
		mainView.Test2();
		//context.SaveChanges();
	}

	// Odd brackets to see eventual memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}