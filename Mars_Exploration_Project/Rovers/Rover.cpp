#include "Rover.h"



Rover::Rover()
{
	checkup_duration = 1;
	speed = 1;
	rover_type = 'P';
	initial_time_till_checkup = 1;
	actual_time_till_checkup = 1;
}

Rover::Rover(int input_checkup_duration, int input_speed, char input_rover_type, int input_initial_time_till_checkup)
{
	checkup_duration = input_checkup_duration;
	speed = input_speed;
	rover_type = input_rover_type;
	initial_time_till_checkup = input_initial_time_till_checkup;
	actual_time_till_checkup = input_initial_time_till_checkup;

}

void Rover::set_speed(int input_speed)
{
	speed = input_speed;
}

int Rover::get_speed()
{
	return speed;
}

void Rover::set_rover_type(int input_rover_type)
{
	rover_type = input_rover_type;
}

char Rover::get_rover_type()
{
	return rover_type;
}

void Rover::set_checkup_duration(int input_checkup_duration)
{
	checkup_duration = input_checkup_duration;
}

int Rover::get_checkup_duration()
{
	return checkup_duration;
}

void Rover::set_initial_time_till_checkup(int input_initial_time)
{
	initial_time_till_checkup = input_initial_time;
	actual_time_till_checkup = input_initial_time;
}

int Rover::get_actual_time_till_checkup()
{
	return actual_time_till_checkup;
}

void Rover::decrement_actual_time_till_checkup()
{
	actual_time_till_checkup--;
}

void Rover::reset_actual_time_till_checkup()
{
	actual_time_till_checkup = initial_time_till_checkup;
}

void Rover::set_mission(Mission* inexecution_mission)
{
	mission = inexecution_mission;
}

int Rover::get_mission_id()
{
	if (!mission)
	{
		return 0;
	}
	return mission->get_id();
}



