#pragma once
#include <iostream>
#include "../Rovers/Rover.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"

#include "../Datastructures/PriQ ADT/PriQ.h"
class Station
{
private:
	/// REMOVE WHEN EVENTS AND MISSIONS ARE COMPLETED
	typedef int Event;
	typedef int Mission;

	/// </summary>
	uint16_t current_day;
	LinkedQueue<int> d;
	PriQ<Rover*> InCheckupPolarRover;
	public:
	Station();
	~Station();



};

