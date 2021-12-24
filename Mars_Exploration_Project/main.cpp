/*
*  -----------Mars Exploration Project-----------
* 
* Team members: 
* 1.
* 2.
* 3.
* 4.
* 
*/

/*
* File: main.cpp 
* 
* Description: Includes main function which executes the simulation
* 
* Author(s): 
* 
* Date Created:  17/12/2021
*/

#include "Misc/Station.h"
#include "Missions/Mission.h"
#include "Rovers/Rover.h"
#include "Datastructures/Queue ADT/LinkedQueue.h"

#include "Datastructures/PriQ ADT/PriQ.h"

#include <iostream>
using namespace std;	

///////////////////////////////////
/*Global Variables*/

///////////////////////////////////
int main()
{
	
	Rover r1;
	Rover* r2;
	Rover* r3;
	Rover *r4;
	Mission m1;
	Mission m2;
	m2.set_id(3);
	r1.set_speed(50);
	m1.set_mission_duration(6);
	m1.set_target_location(150);
	Station home;
	home.pair(&m1, &r1);

	home.App.print_mission_info(&m1);
	home.App.print_rover_info(&r1);
	home.add_polar_rover(5, 99, 99, 99);
	home.add_emergency_rover(3, 88, 88, 77);
	home.add_mountains_rover(2, 33, 44, 66);
	home.PolarRovers.dequeue(r2);
	home.App.print_rover_info(r2);

	home.EmergencyRovers.dequeue(r3);
	home.App.print_rover_info(r3);


	home.MountainRovers.dequeue(r4);
	home.App.print_rover_info(r4);

	cin.get();
	return 0;
}

