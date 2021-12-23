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
	Mission m1;
	r1.set_speed(50);
	m1.set_mission_duration(6);
	m1.set_target_location(150);
	Station station1;
	station1.pair(&m1, &r1);

	station1.App.print_mission_info(&m1);
	station1.App.print_rover_info(&r1);

	cin.get();
	return 0;
}

