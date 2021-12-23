#include "Mission.h"

Mission::Mission()
{
	type = 'p';
	formulation_day = 1;
	target_location = 1;
	mission_duration = 1;
	significance = 1;
	id = 2;
}

Mission::Mission(char input_mission_type, int input_formulation_day, int input_target_location, int input_mission_duration, int input_significance, int input_id)
{
	type = input_mission_type;
	formulation_day = input_formulation_day;
	target_location = input_target_location;
	mission_duration = input_mission_duration;
	significance = input_significance;
	id = input_id;
}

void Mission::set_formulation_day(int input_formulation_day)
{
	formulation_day = input_formulation_day;
}

int Mission::get_formulation_day()
{
	return formulation_day;
}

void Mission::set_mission_type(char input_mission_type)
{
	type = input_mission_type;
}

char Mission::get_mission_type()
{
	return type;
}

void Mission::set_target_location(int input_target_location)
{
	target_location = input_target_location;
}

int Mission::get_target_location()
{
	return target_location;
}

void Mission::set_mission_duration(int input_mission_duration)
{
	mission_duration = input_mission_duration;
}

int Mission::get_mission_duration()
{
	return mission_duration;
}

void Mission::set_significance(int input_significance)
{
	significance = input_significance;
}

int Mission::get_significance()
{
	return significance;
}

void Mission::set_id(int input_id)
{
	id = input_id;
}

int Mission::get_id()
{
	return id;
}
