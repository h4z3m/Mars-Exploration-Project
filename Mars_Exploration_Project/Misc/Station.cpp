#include "Station.h"

Station::Station()
{
	//Initialize current day to 1 at start-up
	current_day = 1;
	//TODO Load from i/p file
	



}

bool IO::IO_ReadFile(PriQ<Event>*& ReturnList)
{

	UI_printString((string*)"Enter filename (including ext): ");
	filename = UI_getString();

	file.open(fileName);
	//Failed to open file
	if (!file.is_open()) {
		return false;
	}
	else {
		//Start loading data into event lists



	}
}

bool IO::IO_OutputFile(PriQ<Event>*& OutputList)
{
	return false;
}

Station::~Station()
{
}
