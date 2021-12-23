#include "Station.h"

Station::Station()
{
	current_day = 1;
	App.UI_printString((const char*)"Constructor of Station class");
	IO_ReadFile(Events);


}

bool Station::IO_ReadFile(LinkedQueue<Event*> & ReturnList)
{
	char counter = 5;
	//Get file name from user
	App.UI_printString((const char*)"Enter filename (including ext): ");
	fileName = App.UI_getString();
	file.open(fileName);
	//Start parsing file
	string rovertypes;
	string roverspeeds;
	string roverdata;
	string line;
	char dummy;

	
	if (file.is_open()) {
		//Start loading data into event lists
		//Parse first 5 lines 
		
		//Number of available rovers of all types
		getline(file, rovertypes);
		stringstream ss(rovertypes);
		while (ss >> total_Mrovers >> total_Provers >> total_Erovers);
		//Rover speeds for all types
		ss.str(""); ss.clear();
		getline(file, roverspeeds);
		ss<<roverspeeds;
		while (ss >> M_Rover_Speed>> P_Rover_Speed>> E_Rover_Speed);
		//Rover max missions, checkup duration for each type
		ss.str(""); ss.clear();
		getline(file, roverdata);
		ss<<roverdata;
		while (ss >> Rover_Max_Missions>> M_Rover_InCheckupDuration >> P_Rover_InCheckupDuration >> E_Rover_InCheckupDuration);
		//Auto promotion
		ss.str(""); ss.clear();
		getline(file, line);
		ss<<line;
		while (ss >> AutoPromotionLimit);
		//Event count
		ss.str(""); ss.clear();
		getline(file, line);
		ss<<line;
		while (ss >> EventCount);
		
	}
	//Failed to open file                             
	else {
		return false;
	}
}

bool Station::IO_OutputFile(LinkedQueue<Event*>*& OutputList)
{
	return false;
}

Station::~Station()
{
}
