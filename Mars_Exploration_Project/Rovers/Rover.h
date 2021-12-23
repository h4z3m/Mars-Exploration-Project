#pragma once
#include "../Missions/Mission.h"
class Rover
{
private:
	int checkup_duration;
	int speed;
	char rover_type;
	int initial_time_till_checkup;
	int actual_time_till_checkup;
	Mission *mission;
public:
	Rover(int input_checkup_duration,int input_speed,char input_rover_type,int input_initial_time_till_checkup);
	void set_speed(int input_speed);
	int get_speed();

	void set_rover_type(int input_rover_type);
	char get_rover_type();

	void set_checkup_duration(int input_checktup_duration);
	int get_checkup_duration();

	void set_initial_time_till_checkup(int input_initial_time);       //set initial and actual time to checkup

	int get_actual_time_till_checkup();
	void decrement_actual_time_till_checkup();
	void reset_actual_time_till_checkup();

	void set_mission(Mission* inexecution_mission);
};

