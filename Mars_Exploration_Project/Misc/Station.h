#pragma once
#include <iostream>
#include "../Datastructures/PriQ ADT/PriQ.h"

#include "../Datastructures/Queue ADT/LinkedQueue.h"
class Station
{
private:
	/// REMOVE WHEN EVENTS AND MISSIONS ARE COMPLETED
	typedef int Event;
	typedef int Mission;
	typedef int Rover;

	/// </summary>
	uint16_t current_day;
	LinkedQueue<Event> EventsQueue;
	
	PriQ<Rover*> PolarRovers;
	LinkedQueue<Rover*> InCheckupPolarRovers;

	PriQ<Rover*> MountainRovers;
	LinkedQueue<Rover*> InCheckupMountainRovers;

	PriQ<Rover*> EmergencyRovers;
	LinkedQueue<Rover*> InCheckupEmergencyRovers;

	PriQ<Mission*> CompletedMissions;
public:
	Station();
	~Station();



};

