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

//sa7 da7 embooo

#include "Datastructures/Queue ADT/LinkedQueue.h"
#include "Datastructures/PriQ ADT/PriQ.h"
#include "Misc/Station.h"
#include <iostream>
using namespace std;	

int main()
{
	
	Rover r1;
	Rover *r2;
	Rover *r3;
	Rover *r4;
	Mission *m1;
	Mission *m2;
	Mission *m3;
	Station home;
	/*
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


	home.formulate_mission('E', 4, 4, 5, 6, 7);
	home.formulate_mission('E', 10, 10, 10, 10, 1);
	home.formulate_mission('P', 55, 5, 5, 5, 5);

	home.EmergencyMissions.dequeue(m1);
	home.App.print_mission_info(m1);
	home.EmergencyMissions.dequeue(m2);
	home.App.print_mission_info(m2);
	home.PolarMissions.dequeue(m3);
	home.App.print_mission_info(m3);
	cin.get();
	*/
	home.add_emergency_rover(3, 88, 88, 77);
	home.formulate_mission('E', 1, 1, 1, 1, 1);
	home.EmergencyMissions.dequeue(m2);
	home.EmergencyRovers.dequeue(r2);
	home.App.print_mission_info(m2);
	home.App.print_rover_info(r2);
	int x = home.get_total_completed_missions();
	cout << x;
	home.pair(m2,r2);
	home.App.print_mission_info(m2);
	home.App.print_rover_info(r2);
	home.retrieve_rover();
	home.App.print_mission_info(m2);
	home.App.print_rover_info(r2);
	x = home.get_total_completed_missions();
	int y = home.get_p_completed_missions();
	int z = home.get_e_completed_missions();
	cout << x<<y<<z;
	return 0;
	
}

