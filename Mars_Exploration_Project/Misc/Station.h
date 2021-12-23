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
	UI App;
	ifstream file;
	string fileName;
	
	/// REMOVE WHEN EVENTS AND MISSIONS ARE COMPLETED
	typedef int Event;
	typedef int Mission;
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

	PriQ<Rover*> InExecutionRovers;

	PriQ<Rover*> PolarRovers;
	PriQ<Rover*> EmergencyRovers;
	PriQ<Rover*> MountainRovers;
	
	LinkedQueue<Rover*> InCheckupPolarRovers;
	LinkedQueue<Rover*> InCheckupEmergencyRovers;
	LinkedQueue<Rover*> InCheckupMountainRovers;
	//Private Utility Functions
	
	bool IO_ReadFile(LinkedQueue<Event*>& ReturnList);
	bool IO_OutputFile(LinkedQueue<Event*>*& OutputList);
	public:
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



};

