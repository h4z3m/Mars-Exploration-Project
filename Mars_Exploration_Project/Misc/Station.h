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

	/// </summary>
	uint16_t current_day;

	LinkedQueue<Event*> Events;

	PriQ<Rover*> InExecutionRovers;

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
	void pair(Mission mission, Rover rover) {
		char rover_type = rover.get_rover_type();
		Mission *temp_mission;
		Rover *temp_rover;
		int piority;
		int speed_of_rover = rover.get_speed();
		int mission_duration = mission.get_mission_duration();
		int mission_location = mission.get_target_location();
		piority = current_day+ mission_duration+(2*((mission_location/speed_of_rover)/25));

		if (rover_type == 'p')
		{
			PolarRovers.dequeue(temp_rover);
			InExecutionRovers.enqueue(temp_rover,piority);
		}
	};


};

