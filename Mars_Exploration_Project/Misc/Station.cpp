#include "Station.h"

Station::Station()
{
	current_day = 1;
	App.UI_printString((const char*)"Constructor of Station class");
	IO_ReadFile(Events);


}

void Station::Init_Rovers(char type, unsigned int count, unsigned int speed, unsigned int InCheckupDuration, unsigned int MaxMissions)
{
	PriQ<Rover*>* tempPtr;
	//Determine type of rover queue to create
	switch (type) {
	case 'E':
		tempPtr = &EmergencyRovers;
		break;
	case 'M':
		tempPtr = &MountainRovers;
		break;

	case 'P':
		tempPtr = &PolarRovers;
		break;
	default:
		return;

	}
	for (unsigned int i = 0; i < count; ++i) {
		Rover* newRover = new Rover(InCheckupDuration, speed, type, MaxMissions);
		//Enqueue new rover and give its speed as priority
		//The higher the speed, the higher the priority
		tempPtr->enqueue(newRover, speed);
	}
}
bool Station::IO_ReadFile(LinkedQueue<Event*>& ReturnList)
{
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
		ss << roverspeeds;
		while (ss >> M_Rover_Speed >> P_Rover_Speed >> E_Rover_Speed);
		//Rover max missions, checkup duration for each type
		ss.str(""); ss.clear();
		getline(file, roverdata);
		ss << roverdata;
		while (ss >> Rover_Max_Missions >> M_Rover_InCheckupDuration >> P_Rover_InCheckupDuration >> E_Rover_InCheckupDuration);
		//Auto promotion
		ss.str(""); ss.clear();
		getline(file, line);
		ss << line;
		while (ss >> AutoPromotionLimit);
		//Event count
		ss.str(""); ss.clear();
		getline(file, line);
		ss << line;
		while (ss >> EventCount);
		//----Start filling rover queues----//
		Init_Rovers('E', total_Erovers, E_Rover_Speed, E_Rover_InCheckupDuration, Rover_Max_Missions);
		Init_Rovers('M', total_Mrovers, M_Rover_Speed, M_Rover_InCheckupDuration, Rover_Max_Missions);
		Init_Rovers('P', total_Provers, P_Rover_Speed, P_Rover_InCheckupDuration, Rover_Max_Missions);
		//----Parse rest of file containing events----//
		uint8 mission_type;
		uint32 event_day;
		uint32 mission_ID;
		uint32 target_loc;
		uint32 mission_duration;
		uint8 mission_significance;
		for (uint32 i = 0; i < EventCount; ++i) {
			getline(file, line);
			if (line.find('F') != string::npos) {
				//Formulate event here
				ss.str(""); ss.clear();
				ss << line;
				while (ss >> dummy >> mission_type >> event_day >> mission_ID >> target_loc >> mission_duration >> mission_significance);
				FormulateEvent* newF_Event = new FormulateEvent(mission_type, event_day, mission_ID, target_loc, mission_duration, mission_significance);
				Events.enqueue(newF_Event);
			}
			else if (line.find('P') != string::npos) {
				//Promote event here
				ss.str(""); ss.clear();
				ss << line;
				while (ss >> dummy >> event_day >> mission_ID);
			}
			else if (line.find('X') != string::npos) {
				//Cancel event here
				ss.str(""); ss.clear();
				ss << line;
				while (ss >> dummy >> event_day >> mission_ID);

			}
			else {

			}
		}
		file.close();
		return true;
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

void Station::pair(Mission mission, Rover rover)
{
	char rover_type = rover.get_rover_type();
	char mission_type = mission.get_mission_type();
	Mission* temp_mission;
	Rover* temp_rover;
	int piority;
	int speed_of_rover = rover.get_speed();
	int mission_duration = mission.get_mission_duration();
	int mission_location = mission.get_target_location();
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
		rover.set_mission(temp_mission);
	}
	else if (mission_type == 'e')
	{
		EmergencyMissions.dequeue(temp_mission);
		rover.set_mission(temp_mission);
	}
	///add for mountain after including linked list
}


Mission* Station::GetRequestedMission(int Id) {
	int i = 1;
	Mission* temp = NULL;
	//if mountainous missons list is not empty
	while (!MountainMissions.isEmpty()) {

		temp = MountainMissions.getEntry(i);
		if (temp) {
			if (temp->get_id() == Id) {
				break;
			}
		}
		else
			i++;
	}

	return temp;
}

void Station::CancelMission(int Id) {

	int i = 1;
	Mission* temp = NULL;
	//while mountainous missons list is not empty
	while (!MountainMissions.isEmpty()) {

		temp = MountainMissions.getEntry(i);
		if (temp) {
			if (temp->get_id() == Id) {
				break;
			}
		}
		else
			i++;
	}

	MountainMissions.DeletePosition(i);
}

void Station::AddEmergencyMission(Mission* M, int Significance) {
	EmergencyMissions.enqueue(M, Significance);
}





