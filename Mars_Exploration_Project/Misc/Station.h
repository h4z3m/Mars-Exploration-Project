#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"UI.h"
#include "../Rovers/Rover.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
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
	
	/// REMOVE WHEN EVENTS AND MISSIONS ARE COMPLETED
	typedef int Event;

	/// </summary>
	uint16_t current_day;

	LinkedQueue<Event*> Events;
	////////ROVERS/////////
	PriQ<Rover*> InExecutionRovers;
	LinkedQueue<Rover*> InCheckupPolarRovers;
	LinkedQueue<Rover*> InCheckupEmergencyRovers;
	LinkedQueue<Rover*> InCheckupMountainRovers;

	////////MISSIONS////////////
	
	//Private Utility Functions
	
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

	///adding rovers to Pque
	void add_polar_rover(int input_number_of_rovers, int SP, int  CP, int N);
	void add_emergency_rover(int input_number_of_rovers, int SE, int  CE, int N);
	void add_mountains_rover(int input_number_of_rovers, int SM, int  CM, int N);
	///////ADD MISSIONS
	void formulate_mission(char type, int ED, int ID, int TLOC, int MDUR, int SIG);

};

