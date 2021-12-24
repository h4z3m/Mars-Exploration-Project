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

void Station::pair(Mission* mission, Rover* rover)
{
	char rover_type = rover->get_rover_type();
	char mission_type = mission->get_mission_type();
	int piority = end_day(mission,rover);
	rover->set_mission(mission);
	InExecutionRovers.enqueue(rover, piority);
	
	
	///add for mountain after including linked list
}



int Station::return_day_of_rover(Rover* rover)
{
	Mission* temp_mission;
	temp_mission = rover->get_mission();
	int piority;
	int speed_of_rover = rover->get_speed();
	int mission_duration = temp_mission->get_mission_duration();
	int mission_location = temp_mission->get_target_location();
	piority = current_day + mission_duration + (2 * ((mission_location / speed_of_rover) / 25));
	return piority;
}
///////////////////STATS////////////////////
int Station::get_e_completed_missions()
{
	return E_completed_missions;
}

int Station::get_p_completed_missions()
{
	return P_completed_missions;
}

int Station::get_m_completed_missions()
{
	return M_completed_missions;
}

void Station::increment_e_completed_missions()
{
	E_completed_missions++;
}

void Station::increment_p_completed_missions()
{
	P_completed_missions++;
}

void Station::increment_m_completed_missions()
{
	M_completed_missions++;
}

int Station::get_total_completed_missions()
{
	return E_completed_missions+P_completed_missions+M_completed_missions;
}

/// ////////////////////////STATS//////////////////////
int Station::end_day(Mission* mission, Rover* rover)
{
	int piority;
	int speed_of_rover = rover->get_speed();
	int mission_duration = mission->get_mission_duration();
	int mission_location = mission->get_target_location();
	piority = current_day + mission_duration + (2 * ((mission_location / speed_of_rover) / 25));
	return piority;
}

void Station::add_polar_rover(int input_number_of_rovers, int SP, int CP, int N)
{
	Rover* temp_rover;
	for (int i = 0; i < input_number_of_rovers; i++)
	{
		temp_rover = new Rover(CP, SP, 'P', N);
		PolarRovers.enqueue(temp_rover,SP);
		
	}
}

void Station::add_emergency_rover(int input_number_of_rovers, int SE, int CE, int N)
{
	Rover* temp_rover;
	for (int i = 0; i < input_number_of_rovers; i++)
	{
		temp_rover = new Rover(CE, SE, 'E', N);
		EmergencyRovers.enqueue(temp_rover, SE);

	}
}

void Station::add_mountains_rover(int input_number_of_rovers, int SM, int CM, int N)
{
	Rover* temp_rover;
	for (int i = 0; i < input_number_of_rovers; i++)
	{
		temp_rover = new Rover(CM, SM, 'M', N);
		MountainRovers.enqueue(temp_rover, SM);

	}
}

void Station::formulate_mission(char type, int ED, int ID, int TLOC, int MDUR, int SIG)
{

	Mission* temp_mission;
	temp_mission = new Mission(type, ED, TLOC, MDUR, SIG, ID);
	if (type =='M')
	{
		/////enqueu in mountain when linked list is made
	}
	else if (type == 'E') 
	{
		EmergencyMissions.enqueue(temp_mission, SIG);
	}
	else if (type == 'P')
	{
		PolarMissions.enqueue(temp_mission);
	}
}

void Station::retrieve_rover()
{
	Rover* temp_rover;
	Mission* temp_mission;
	while (InExecutionRovers.peek(temp_rover) && return_day_of_rover(temp_rover)==2)
	{
		InExecutionRovers.dequeue(temp_rover);
		CompletedMissions.enqueue(temp_rover->get_mission(), 1);
		temp_rover->decrement_actual_time_till_checkup();
		temp_mission = temp_rover->get_mission();
		temp_rover->set_mission(nullptr);
		if (temp_rover->get_actual_time_till_checkup() == 0)
		{
			if (temp_rover->get_rover_type() == 'M')
			{
				InCheckupMountainRovers.enqueue(temp_rover);
			}
			else if (temp_rover->get_rover_type() == 'E') 
			{
				InCheckupEmergencyRovers.enqueue(temp_rover);
			}
			else
			{
				InCheckupPolarRovers.enqueue(temp_rover);
			}
		}
		else 
		{
			if (temp_rover->get_rover_type() == 'M')
			{
				MountainRovers.enqueue(temp_rover, temp_rover->get_speed());
			}
			else if (temp_rover->get_rover_type() == 'E')
			{
				EmergencyRovers.enqueue(temp_rover, temp_rover->get_speed());
			}
			else
			{
				PolarRovers.enqueue(temp_rover,temp_rover->get_speed());
			}
		
		}
		if (temp_mission->get_mission_type()=='E')
		{
			increment_e_completed_missions();
		}
		else if (temp_mission->get_mission_type() == 'M')
		{
			increment_m_completed_missions();
		}
		else if (temp_mission->get_mission_type() == 'P')
		{
			increment_p_completed_missions();
		}

	}
}





