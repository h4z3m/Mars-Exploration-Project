#include "Station.h"

Station::Station()
{
	current_day = 1;
	App.UI_printString((const char*)"Constructor of Station class");
	IO_ReadFile(Events);


}

void Station::Simulate_Station()
{
	Mission* MissionOfToday = nullptr;
	Event* EventOfToday = nullptr;
	
	while (!EmergencyMissions.isEmpty() || !PolarMissions.isEmpty() || !MountainMissions.isEmpty() || !InExecutionRovers.isEmpty() || !Events.isEmpty() || !InCheckupEmergencyRovers.isEmpty() || !InCheckupMountainRovers.isEmpty() || !InCheckupPolarRovers.isEmpty()) {
		//check autopromotions 0
		check_auto_promotion();
		// 1 - Gather daily events
		while (Events.peek(EventOfToday)) {
			//Check if event day matches current day
			if (EventOfToday->getEventDay() == current_day) {
				//Remove from queue
				Events.dequeue(EventOfToday);
				//Check for type of event
				if (dynamic_cast<FormulationEvent*>(EventOfToday)) {
					EventOfToday->Execute();
				}
				else if (dynamic_cast<CancellationEvent*>(EventOfToday)) {
					EventOfToday->Execute();
				}
				else {
					dynamic_cast<PromotionEvent*>(EventOfToday);
					EventOfToday->Execute();
				}
			}
			else {
				break;
			}

		}
		// 2 - Retrieve incoming rovers
		retrieve_rover();
		retrieve_rover_from_checkup();
		// 3 - Pair available rovers to corresponding missions
		while (!EmergencyMissions.isEmpty())
		{
			Rover* Outgoing_Rover = nullptr;
			Mission* Outgoing_Mission = nullptr;
			//Check emergency missions first
			if (!EmergencyRovers.isEmpty()) {
				EmergencyRovers.dequeue(Outgoing_Rover);
				EmergencyMissions.dequeue(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);
				/*	App.UI_printString("em mission - em rover\n");*/
			}
			else if (!MountainRovers.isEmpty()) {
				MountainRovers.dequeue(Outgoing_Rover);
				EmergencyMissions.dequeue(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);
				/*	App.UI_printString("em mission - mountain rover\n");*/


			}
			else if (!PolarRovers.isEmpty()) {
				PolarRovers.dequeue(Outgoing_Rover);
				EmergencyMissions.dequeue(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);
				/*App.UI_printString("em mission - polar rover\n");*/

			}
			else {
				/*	App.UI_printString((const char*)"No rovers available for em missions\n");*/
				break;
			}
		}
		while (!PolarMissions.isEmpty())
		{
			Rover* Outgoing_Rover = nullptr;
			Mission* Outgoing_Mission = nullptr;
			//Check emergency missions first
			if (!PolarRovers.isEmpty()) {
				PolarRovers.dequeue(Outgoing_Rover);
				PolarMissions.dequeue(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);
				/*	App.UI_printString("polar mission - polar rover\n");*/

			}
			else {
				/*App.UI_printString((const char*)"No rovers available for polar missions\n");*/
				break;
			}
		}
		while (!MountainMissions.isEmpty())
		{
			Rover* Outgoing_Rover = nullptr;
			Mission* Outgoing_Mission = nullptr;
			//Check emergency missions first
			if (!MountainRovers.isEmpty()) {
				MountainRovers.dequeue(Outgoing_Rover);
				MountainMissions.deqHead(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);
				/*App.UI_printString("em mission - mountain rover\n");*/

			}
			else if (!EmergencyRovers.isEmpty()) {
				EmergencyRovers.dequeue(Outgoing_Rover);
				MountainMissions.deqHead(Outgoing_Mission);
				pair(Outgoing_Mission, Outgoing_Rover);

			}

			else {
				//App.UI_printString((const char*)"No rovers available for mountain missions\n");
				break;
			}
		}
		if (display_mode != Silent) {
			print_day();
			App.UI_clear_screen();
		}
		++current_day;
	}
	if (display_mode != Silent) {
		print_day();
	}
	IO_OutputFile();
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
		Rover* newRover = new Rover(InCheckupDuration, speed, type, MaxMissions, i + 1);
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
				FormulationEvent* newF_Event = new FormulationEvent(mission_type, event_day, mission_ID, target_loc, mission_duration, mission_significance,PolarMissions,EmergencyMissions,MountainMissions);
				Events.enqueue(newF_Event);
			}
			else if (line.find('P') != string::npos) {
				//Promote event here
				ss.str(""); ss.clear();
				ss << line;
				while (ss >> dummy >> event_day >> mission_ID);
				PromotionEvent* newP_Event = new PromotionEvent(mission_ID, event_day, PolarMissions, EmergencyMissions, MountainMissions);
				Events.enqueue(newP_Event);


				while (ss >> dummy >> event_day >> mission_ID);
			}
			else if (line.find('X') != string::npos) {
				//Cancel event here
				ss.str(""); ss.clear();
				ss << line;
				while (ss >> dummy >> event_day >> mission_ID);
				CancellationEvent* newC_Event = new CancellationEvent(mission_ID, event_day, PolarMissions, EmergencyMissions, MountainMissions);
				Events.enqueue(newC_Event);
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
bool Station::IO_OutputFile()
{
	ofstream outputfile;
	outputfile.open("output.txt");
	outputfile.precision(3);
	App.UI_printString((const char*)"\nWriting to output file...");
	///write output here
	outputfile << "CD   ID   FD   WD   ED" << endl;
	Mission* tempMission = nullptr;
	float total_wait = 0;
	float total_execution = 0;
	int total_rovers = EmergencyRovers.get_count() + PolarRovers.get_count() + MountainRovers.get_count();
	PriNode<Mission*>* emNode = CompletedMissions.getPFront();
	while (emNode) {
		tempMission = emNode->getItem();
		int CD = tempMission->get_cd();
		int ID = tempMission->get_id();
		int FD = tempMission->get_formulation_day();
		int WD = tempMission->get_wd();
		int ED = tempMission->get_ed();
		total_wait = total_wait + WD;
		total_execution = total_execution + ED;
		outputfile << CD << "    " << ID << "    " << FD << "    " << WD << "    " << ED << endl;
		emNode = emNode->getNext();
	}
	outputfile << "******************************************" << endl;
	outputfile << "******************************************" << endl;
	outputfile << "Missions:" << CompletedMissions.get_count() << "    ";
	outputfile << "[M: " << M_completed_missions << ", P:" << P_completed_missions << ", E:" << E_completed_missions << "]" << endl;
	outputfile << "Rovers: " << total_rovers << "    [M:" << MountainRovers.get_count() << ", P:" << PolarRovers.get_count() << ", E:" << EmergencyRovers.get_count() << "]" << endl;
	outputfile << "Average Wait = " << total_wait / CompletedMissions.get_count() << ", Avg Exec = " << total_execution / CompletedMissions.get_count() << endl;
	outputfile << "Auto-promoted: " << 100 * (total_auto_promotion / total_mountain_formulated)<<"%";



	outputfile.close();
	return false;
}
Station::~Station()
{
}
void Station::pair(Mission* mission, Rover* rover)
{
	//char rover_type = rover->get_rover_type();
	//char mission_type = mission->get_mission_type();
	int piority = end_day(mission, rover);
	rover->set_mission(mission);
	mission->set_start_day(current_day);
	mission->set_wd();
	InExecutionRovers.enqueue(rover, -piority);


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
	piority = temp_mission->get_start_day() + mission_duration + (2 * ((mission_location / speed_of_rover) / 25));
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
	return E_completed_missions + P_completed_missions + M_completed_missions;
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
//
//void Station::add_polar_rover(int input_number_of_rovers, int SP, int CP, int N)
//{
//	Rover* temp_rover;
//	for (int i = 0; i < input_number_of_rovers; i++)
//	{
//		temp_rover = new Rover(CP, SP, 'P', N);
//		PolarRovers.enqueue(temp_rover, SP);
//
//	}
//}
//
//void Station::add_emergency_rover(int input_number_of_rovers, int SE, int CE, int N)
//{
//	Rover* temp_rover;
//	for (int i = 0; i < input_number_of_rovers; i++)
//	{
//		temp_rover = new Rover(CE, SE, 'E', N);
//		EmergencyRovers.enqueue(temp_rover, SE);
//
//	}
//}
//
//void Station::add_mountains_rover(int input_number_of_rovers, int SM, int CM, int N)
//{
//	Rover* temp_rover;
//	for (int i = 0; i < input_number_of_rovers; i++)
//	{
//		temp_rover = new Rover(CM, SM, 'M', N);
//		MountainRovers.enqueue(temp_rover, SM);
//
//	}
//}

void Station::set_display_mode()
{
	do {
		App.UI_printString((const char*)"Please choose a display mode:");

		App.UI_printString((const char*)"\n1 - Interactive mode");
		App.UI_printString((const char*)"\n2 - Step by step mode");
		App.UI_printString((const char*)"\n3 - Silent mode");
		
		display_mode = App.UI_getChar();
	
	} while (display_mode != Interactive && display_mode != StepByStep && display_mode != Silent);
}

void Station::retrieve_rover()
{
	Rover* temp_rover;
	Mission* temp_mission;
	while (InExecutionRovers.peek(temp_rover) && return_day_of_rover(temp_rover) == current_day)
	{
		InExecutionRovers.dequeue(temp_rover);
		// TODO : COMPUTE RETURN DAY PRIORITY///////////////////
		temp_mission = temp_rover->get_mission();
		temp_mission->set_cd(current_day);
		CompletedMissions.enqueue(temp_mission, -temp_mission->get_cd());
		temp_rover->decrement_actual_time_till_checkup();


		temp_rover->set_mission(nullptr);
		if (temp_rover->get_actual_time_till_checkup() == 0)
		{
			if (temp_rover->get_rover_type() == MOUNTAIN)
			{
				temp_rover->set_day_to_get_out_of_checkup(current_day + M_Rover_InCheckupDuration);
				InCheckupMountainRovers.enqueue(temp_rover);
			}
			else if (temp_rover->get_rover_type() == EMERGENCY)
			{
				temp_rover->set_day_to_get_out_of_checkup(current_day + E_Rover_InCheckupDuration);
				InCheckupEmergencyRovers.enqueue(temp_rover);
			}
			else
			{
				temp_rover->set_day_to_get_out_of_checkup(current_day + P_Rover_InCheckupDuration);
				InCheckupPolarRovers.enqueue(temp_rover);
			}
		}
		else
		{
			if (temp_rover->get_rover_type() == MOUNTAIN)
			{
				MountainRovers.enqueue(temp_rover, temp_rover->get_speed());
				////TODO: REMOVE WHEN FINISHED TESTING

				//App.UI_printString((const char*)"M - Returned on ");
				//cout << current_day;
			}
			else if (temp_rover->get_rover_type() == EMERGENCY)
			{
				EmergencyRovers.enqueue(temp_rover, temp_rover->get_speed());

				////TODO: REMOVE WHEN FINISHED TESTING
				//App.UI_printString((const char*)"E - Returned on ");
				//cout << current_day;

			}
			else
			{
				PolarRovers.enqueue(temp_rover, temp_rover->get_speed());


				//TODO: REMOVE WHEN FINISHED TESTING
				//App.UI_printString((const char*)"P - Returned on ");
				//cout << current_day;

			}

		}
		if (temp_mission->get_mission_type() == EMERGENCY)
		{
			increment_e_completed_missions();
		}
		else if (temp_mission->get_mission_type() == MOUNTAIN)
		{
			increment_m_completed_missions();
		}
		else if (temp_mission->get_mission_type() == POLAR)
		{
			increment_p_completed_missions();
		}

	}
}

void Station::retrieve_rover_from_checkup()
{
	Rover* temp_rover;
	Mission* temp_mission;
	while (InCheckupEmergencyRovers.peek(temp_rover) && temp_rover->get_day_to_get_out_of_checkup() == current_day)
	{
		InCheckupEmergencyRovers.dequeue(temp_rover);
		EmergencyRovers.enqueue(temp_rover, temp_rover->get_speed());
		/*App.UI_printString((const char*)"E - rover out of checkup ");*/
	}
	while (InCheckupMountainRovers.peek(temp_rover) && temp_rover->get_day_to_get_out_of_checkup() == current_day)
	{
		InCheckupMountainRovers.dequeue(temp_rover);
		MountainRovers.enqueue(temp_rover, temp_rover->get_speed());
	}
	while (InCheckupPolarRovers.peek(temp_rover) && temp_rover->get_day_to_get_out_of_checkup() == current_day)
	{
		InCheckupPolarRovers.dequeue(temp_rover);
		PolarRovers.enqueue(temp_rover, temp_rover->get_speed());
	}
}

void Station::print_waiting_missions() {
	stringstream buff;

	/***************Waiting Missions line******************/
	buff << BOLDYELLOW << EmergencyMissions.get_count() + PolarMissions.get_count() + MountainMissions.getCount() << RED << "  Waiting " << YELLOW << "Missions: " << WHITE << "[";

	/* Get waiting emergency missions*/
	App.UI_printStringColor(BOLDWHITE, buff);
	Mission* tempMission = nullptr;

	PriNode<Mission*>* emNode = EmergencyMissions.getPFront();
	while (emNode) {
		tempMission = emNode->getItem();

		buff << tempMission->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (emNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		emNode = emNode->getNext();
	}
	buff << " ] ";
	App.UI_printStringColor(WHITE, buff);


	/* Get waiting polar missions*/
	buff << " ( ";
	App.UI_printStringColor(BOLDWHITE, buff);

	tempMission = nullptr;
	Node<Mission*>* pNode = PolarMissions.getFront();

	while (pNode) {
		tempMission = pNode->getItem();
		buff << tempMission->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (pNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		pNode = pNode->getNext();
	}
	buff << " ) ";
	App.UI_printStringColor(WHITE, buff);

	/* Get waiting mountain missions*/
	buff << "{ ";
	App.UI_printStringColor(WHITE, buff);
	tempMission = nullptr;
	LNode<Mission*>* mNode = MountainMissions.getHead();
	while (mNode) {
		tempMission = mNode->getItem();

		buff << tempMission->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (mNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		mNode = mNode->getNext();
	}
	buff << "} " << endl;
	App.UI_printStringColor(WHITE, buff);
}
void Station::print_inexec_missionsrovers() {

	stringstream buff;
	/**Emergency Missions/Rovers**/
	int execution_missions_count = InExecutionRovers.get_count();
	buff << BOLDRED << execution_missions_count << YELLOW << " In-Execution " << CYAN << "Missions" << WHITE << "/" << YELLOW << "Rovers: " << WHITE << "[ ";
	App.UI_printStringColor(WHITE, buff);
	Rover* tempRover = nullptr;
	PriNode<Rover*>* emRoverNode = InExecutionRovers.getPFront();
	while (emRoverNode) {
		tempRover = emRoverNode->getItem();
		if (tempRover->get_rover_type() == 'E') {
			buff << tempRover->get_mission_id();
			buff << "/" << tempRover->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		emRoverNode = emRoverNode->getNext();
	}
	buff << " ] ";
	App.UI_printStringColor(WHITE, buff);


	/**Polar Missions/Rovers**/
	buff << " ( ";
	App.UI_printStringColor(WHITE, buff);
	tempRover = nullptr;
	PriNode<Rover*>* pRoverNode = InExecutionRovers.getPFront();
	while (pRoverNode) {
		tempRover = pRoverNode->getItem();

		if (tempRover->get_rover_type() == 'P') {
			buff << tempRover->get_mission_id();
			buff << "/" << tempRover->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		pRoverNode = pRoverNode->getNext();
	}
	buff << " ) ";
	App.UI_printStringColor(WHITE, buff);


	/**Mountain Missions/Rovers**/
	buff << " { ";
	App.UI_printStringColor(WHITE, buff);
	tempRover = nullptr;
	PriNode<Rover*>* mRoverNode = InExecutionRovers.getPFront();

	while (mRoverNode) {
		tempRover = mRoverNode->getItem();

		if (tempRover->get_rover_type() == 'M') {
			buff << tempRover->get_mission_id();
			buff << "/" << tempRover->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}


		mRoverNode = mRoverNode->getNext();
	}
	buff << " } " << endl;
	App.UI_printStringColor(WHITE, buff);
}
void Station::print_avail_rovers()
{
	stringstream buff;
	/**Emergency Missions/Rovers**/
	int total_avail_rovers = EmergencyRovers.get_count() + PolarRovers.get_count() + MountainRovers.get_count();
	buff << BOLDRED << total_avail_rovers << GREEN << " Available" << YELLOW << " Rovers: " << WHITE << "[";
	App.UI_printStringColor(WHITE, buff);
	Rover* tempRover = nullptr;
	PriNode<Rover*>* emRoverNode = EmergencyRovers.getPFront();
	while (emRoverNode) {
		tempRover = emRoverNode->getItem();

		buff << tempRover->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (emRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		emRoverNode = emRoverNode->getNext();
	}
	buff << " ] ";
	App.UI_printStringColor(WHITE, buff);


	/**Polar Missions/Rovers**/
	buff << " ( ";
	App.UI_printStringColor(WHITE, buff);
	tempRover = nullptr;
	PriNode<Rover*>* pRoverNode = PolarRovers.getPFront();
	while (pRoverNode) {
		tempRover = pRoverNode->getItem();

		buff << tempRover->get_id();

		App.UI_printStringColor(WHITE, buff);

		if (pRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		pRoverNode = pRoverNode->getNext();
	}
	buff << " ) ";
	App.UI_printStringColor(WHITE, buff);


	/**Mountain Missions/Rovers**/
	buff << " { ";
	App.UI_printStringColor(WHITE, buff);
	tempRover = nullptr;
	PriNode<Rover*>* mRoverNode = MountainRovers.getPFront();

	while (mRoverNode) {
		tempRover = mRoverNode->getItem();

		buff << tempRover->get_id();

		App.UI_printStringColor(WHITE, buff);

		if (mRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		mRoverNode = mRoverNode->getNext();
	}
	buff << " } " << endl;
	App.UI_printStringColor(WHITE, buff);
}
void Station::print_incheckup_rovers()
{
	stringstream buff;

	/* Display current day*/
	int total_incheckup_rovers = InCheckupEmergencyRovers.get_count() + InCheckupMountainRovers.get_count() + InCheckupPolarRovers.get_count();
	buff << BOLDMAGENTA << total_incheckup_rovers << RED << "  In-Checkup " << YELLOW << "Rovers: " << WHITE << " [ ";

	/* Get waiting emergency missions*/
	App.UI_printStringColor(BOLDWHITE, buff);
	Rover* tempRover = nullptr;

	Node<Rover*>* emRoverNode = InCheckupEmergencyRovers.getFront();
	while (emRoverNode) {
		tempRover = emRoverNode->getItem();

		buff << tempRover->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (emRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		emRoverNode = emRoverNode->getNext();
	}
	buff << " ] ";
	App.UI_printStringColor(WHITE, buff);


	/* Get waiting polar missions*/
	buff << " (";
	App.UI_printStringColor(BOLDWHITE, buff);

	tempRover = nullptr;
	Node<Rover*>* pRoverNode = InCheckupPolarRovers.getFront();

	while (pRoverNode) {
		tempRover = pRoverNode->getItem();
		buff << tempRover->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (pRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		pRoverNode = pRoverNode->getNext();
	}
	buff << " ) ";
	App.UI_printStringColor(WHITE, buff);

	/* Get waiting mountain missions*/
	buff << "{ ";
	App.UI_printStringColor(WHITE, buff);
	tempRover = nullptr;
	Node<Rover*>* mRoverNode = InCheckupMountainRovers.getFront();
	while (mRoverNode) {
		tempRover = mRoverNode->getItem();

		buff << tempRover->get_id();
		App.UI_printStringColor(WHITE, buff);

		if (mRoverNode->getNext()) {
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}

		mRoverNode = mRoverNode->getNext();
	}
	buff << "} " << endl;
	App.UI_printStringColor(WHITE, buff);
}
void Station::print_completed_missions()
{
	stringstream buff;

	/***************Waiting Missions line******************/
	buff << BOLDMAGENTA << CompletedMissions.get_count() << GREEN << "  Completed" << CYAN << " Missions: " << WHITE << " [ ";

	/* Get waiting emergency missions*/
	App.UI_printStringColor(BOLDWHITE, buff);
	Mission* tempMission = nullptr;

	PriNode<Mission*>* emNode = CompletedMissions.getPFront();
	while (emNode) {
		tempMission = emNode->getItem();
		if (tempMission->get_mission_type() == 'E') {
			buff << tempMission->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}



		emNode = emNode->getNext();
	}
	buff << " ] ";
	App.UI_printStringColor(WHITE, buff);


	/* Get waiting polar missions*/
	buff << " (";
	App.UI_printStringColor(BOLDWHITE, buff);

	tempMission = nullptr;
	PriNode<Mission*>* pNode = CompletedMissions.getPFront();

	while (pNode) {
		tempMission = pNode->getItem();
		if (tempMission->get_mission_type() == 'P') {
			buff << tempMission->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}


		pNode = pNode->getNext();
	}
	buff << " ) ";
	App.UI_printStringColor(WHITE, buff);

	/* Get waiting mountain missions*/
	buff << "{ ";
	App.UI_printStringColor(WHITE, buff);
	tempMission = nullptr;
	PriNode<Mission*>* mNode = CompletedMissions.getPFront();
	while (mNode) {
		tempMission = mNode->getItem();

		if (tempMission->get_mission_type() == 'M') {
			buff << tempMission->get_id();
			App.UI_printStringColor(WHITE, buff);
			buff << " , ";
			App.UI_printStringColor(BLUE, buff);
		}



		mNode = mNode->getNext();
	}
	buff << "} " << endl;
	App.UI_printStringColor(WHITE, buff);
}
void Station::print_line() {
	stringstream str;
	str << "-------------------------------------------------------------------------------" << endl;
	App.UI_printStringColor(WHITE, str);
}
void Station::print_day() {
	stringstream ss;
	char dummy;
	switch (display_mode) {
	case Interactive:
		ss << "Interactive Mode" << endl;
		App.UI_printStringColor(BOLDWHITE, ss);
		break;
	case StepByStep:
		ss << "Step by Step Mode" << endl;
		App.UI_printStringColor(BOLDWHITE, ss);
		break;
	case Silent:
		ss << "Silent Mode" << endl;
		App.UI_printStringColor(BOLDWHITE, ss);
		break;

	}
	ss << WHITE << "Current day: " << current_day << endl;
	App.UI_printStringColor(BOLDWHITE, ss);
	/*********Waiting missions*********/
	print_waiting_missions();
	print_line();
	/*********In execution missions/rovers***/
	print_inexec_missionsrovers();
	print_line();
	/*********Available rovers*********/
	print_avail_rovers();
	print_line();
	/*********In checkup rovers*********/
	print_incheckup_rovers();
	print_line();
	/*********Completed missions*********/
	print_completed_missions();
	print_line();
	switch (display_mode) {
	case Interactive:
		App.UI_WaitKeyPress();
		break;
	case StepByStep:
		App.UI_DelaySeconds(1);

		break;
	case Silent:

		break;
	}
	return;
}

void Station::check_auto_promotion()
{
	Mission* tempMission = nullptr;
	LNode<Mission*>* mNode = MountainMissions.getHead();
	int counter_of_mission = 1;
	int mountaincount = MountainMissions.getCount();
	while (counter_of_mission <= mountaincount) {
		tempMission = mNode->getItem();

		if ((current_day - tempMission->get_formulation_day()) >= AutoPromotionLimit)
		{
			mNode = mNode->getNext();
			tempMission->set_mission_type(EMERGENCY);
			EmergencyMissions.enqueue(tempMission, tempMission->get_significance());
			MountainMissions.DeletePosition(counter_of_mission);
			mountaincount--;
			total_auto_promotion++;

		}
		else
		{
			counter_of_mission++;
			mNode = mNode->getNext();
		}

	}
}
