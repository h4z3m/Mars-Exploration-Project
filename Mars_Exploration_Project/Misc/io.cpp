#include "IO.h"
#include "UI.h"
IO::IO()
{

}

bool IO::IO_ReadFile(PriQ<Event>*& ReturnList)
{
	
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

IO::~IO()
{
}
