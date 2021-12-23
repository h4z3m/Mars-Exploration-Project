#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"UI.h"
#include "../Rovers/Rover.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
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
	uint16_t current_day;

	LinkedQueue<Event*> Events;

	PriQ<Mission*> InExecutionMissions;

	PriQ<Rover*> PolarRovers;
	PriQ<Rover*> EmergencyRovers;
	PriQ<Rover*> MountainRovers;
	
	LinkedQueue<Rover*> InCheckupPolarRovers;
	LinkedQueue<Rover*> InCheckupEmergencyRovers;
	LinkedQueue<Rover*> InCheckupMountainRovers;
	//Private Utility Functions

	bool IO_ReadFile(PriQ<Event>*& ReturnList);
	bool IO_OutputFile(PriQ<Event>*& OutputList);
	public:
	Station();
	//Public Member Functions
	~Station();



};

