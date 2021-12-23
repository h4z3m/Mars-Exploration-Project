#include "Station.h"

Station::Station()
{
	current_day = 1;
	App.UI_printString((const char*)"Constructor of Station class");
	IO_ReadFile(Events);

	

}

bool Station::IO_ReadFile(LinkedQueue<Event*> & ReturnList)
{
	//Get file name from user
	App.UI_printString((const char*)"Enter filename (including ext): ");
	fileName = App.UI_getString();
	file.open(fileName);
	//Start parsing file
	string stline;
	//Failed to open file
	if (!file.is_open()) {
		return false;
	}                                 
	else {
		//Start loading data into event lists

	}
}

bool Station::IO_OutputFile(LinkedQueue<Event*>*& OutputList)
{
	return false;
}

Station::~Station()
{
}

void Station::pair(Mission* mission, Rover* rover)
{
	char rover_type = rover->get_rover_type();
	char mission_type = mission->get_mission_type();
	Mission* temp_mission;
	Rover* temp_rover;
	int piority;
	int speed_of_rover = rover->get_speed();
	int mission_duration = mission->get_mission_duration();
	int mission_location = mission->get_target_location();
	piority = current_day + mission_duration + (2 * ((mission_location / speed_of_rover) / 25));

	if (rover_type == 'p')
	{
		PolarRovers.dequeue(temp_rover);
		InExecutionRovers.enqueue(temp_rover, -piority);
	}
	else if (rover_type == 'e')
	{
		EmergencyRovers.dequeue(temp_rover);
		InExecutionRovers.enqueue(temp_rover, -piority);

	}
	else if (rover_type == 'm')
	{
		MountainRovers.dequeue(temp_rover);
		InExecutionRovers.enqueue(temp_rover, -piority);
	}

	if (mission_type == 'p')
	{
		PolarMissions.dequeue(temp_mission);
		rover->set_mission(temp_mission);
	}
	else if (mission_type == 'e')
	{
		EmergencyMissions.dequeue(temp_mission);
		rover->set_mission(temp_mission);
	}

	rover->set_mission(mission);
	///add for mountain after including linked list
}
