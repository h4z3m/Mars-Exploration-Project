#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"UI.h"
#include "../Events/FormulationEvent.h"
#include"common_types.h"
#include "../Rovers/Rover.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/List ADT/LinkedList.h"
/*
* Class: Station
* 
* Description:
* 
* This class is the maestro class that manages the system. It should have member functions to:
*	1- At program startup, open the input file and load rovers data to fill rovers list(s) and to load
*	the events list.
*	2- One each day,
*	a. Execute the events that should be executed at that day
*	b. Check waiting mission to assign them to available rovers
*	c. Move missions from waiting to in-execution to completed
*	d. Move rovers from available to in-execution to checkup to available again
*	e. Collect statistics that are needed to create output file
*	f. Calls UI class functions to print day details on the output screen
*	3- Produce the output file at the end of simulation
*/
class Station
{
private:
	ifstream file;
	string fileName;
	////STATS//
	int E_completed_missions =0;
	int M_completed_missions =0;
	int P_completed_missions =0;
	/// REMOVE WHEN EVENTS AND MISSIONS ARE COMPLETED
	//typedef int Event;

	/// </summary>
	unsigned int current_day;
	unsigned int total_Erovers;
	unsigned int total_Provers;
	unsigned int total_Mrovers;

	unsigned int M_Rover_Speed;
	unsigned int P_Rover_Speed;
	unsigned int E_Rover_Speed;

	unsigned int Rover_Max_Missions;
	
	unsigned int M_Rover_InCheckupDuration;
	unsigned int P_Rover_InCheckupDuration;
	unsigned int E_Rover_InCheckupDuration;

	unsigned int AutoPromotionLimit;
	unsigned int EventCount;
	LinkedQueue<Event*> Events;
	////////ROVERS/////////
	PriQ<Rover*> InExecutionRovers;
	PriQ<Mission*> CompletedMissions;
	LinkedQueue<Rover*> InCheckupPolarRovers;
	LinkedQueue<Rover*> InCheckupEmergencyRovers;
	LinkedQueue<Rover*> InCheckupMountainRovers;
	////////MISSIONS////////////
	PriQ<Mission*> EmergencyMissions;
	LinkedQueue<Mission*> PolarMissions;
	//Private Utility Functions
	template<typename U,typename... Types>
	U IO_ReadLine(ifstream file, U data1,Types... data2);
	void Init_Rovers(char type, unsigned int count, unsigned int speed, unsigned int Rover_InCheckupDuration, unsigned int Rover_MaxMissions);
	bool IO_ReadFile(LinkedQueue<Event*>& ReturnList);
	bool IO_OutputFile(LinkedQueue<Event*>*& OutputList);
	public:
		/// /return these private///
		UI App;
		
		PriQ<Rover*> PolarRovers;
		PriQ<Rover*> EmergencyRovers;
		PriQ<Rover*> MountainRovers;
		PriQ<Mission*> EmergencyMissions;
		LinkedQueue<Mission*> PolarMissions;

	/*
	* Function: Station (Constructor)
	* Description: 
	*	1. Read input file at startup
	*	2. Load events, rovers, and mission queues
	*		
	*/
	Station();
	//Public Member Functions
	~Station();
	void pair(Mission *mission, Rover *rover);
	///////////Ending day of missions
	int end_day(Mission* mission, Rover* rover);
	///////////////////THIS FUNCTION PROBABLY DOESNT WORK BUT WHO KNOWS/////////////
	int return_day_of_rover(Rover* rover);
	///////////////////THIS FUNCTION PROBABLY DOESNT WORK BUT WHO KNOWS/////////////
	//////////////STATS//////////////
	int get_e_completed_missions();
	int get_p_completed_missions();
	int get_m_completed_missions();
	void increment_e_completed_missions();
	void increment_p_completed_missions();
	void increment_m_completed_missions();
	int get_total_completed_missions();
	////////////////////STATS//////////////////
	
	///adding rovers to Pque
	void add_polar_rover(int input_number_of_rovers, int SP, int  CP, int N);
	void add_emergency_rover(int input_number_of_rovers, int SE, int  CE, int N);
	void add_mountains_rover(int input_number_of_rovers, int SM, int  CM, int N);
	///////ADD MISSIONS
	void formulate_mission(char type, int ED, int ID, int TLOC, int MDUR, int SIG);

	void retrieve_rover();
};
