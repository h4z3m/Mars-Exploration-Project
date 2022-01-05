#include "UI.h"

void UI::UI_printString(const char *st)
{
	cout << st << endl;

}

string UI::UI_getString()
{
	string newString;
	cin >> newString;
	return newString;
}

char UI::UI_getChar()
{
	char newChar;
	cin >> newChar;
	return newChar;
}

void UI::UI_Interactive_Mode(void)
{
	
}

void UI::UI_Step_By_Step(void)
{
}

void UI::UI_Silent_Mode(void)
{
}

void UI::print_rover_info(Rover* r)
{
	int checkup_duration = r->get_checkup_duration();
	int speed = r->get_speed();
	char rover_type = r->get_rover_type();
	int actual_time_till_checkup = r->get_actual_time_till_checkup();
	int current_mission_id = r->get_mission_id();
	cout << checkup_duration << "  " << speed << "  " << rover_type << "  " << actual_time_till_checkup<< "   "<<current_mission_id<<endl;


}

void UI::print_mission_info(Mission *mission)
{
	char mission_type = mission->get_mission_type();
	int mission_duration = mission->get_mission_duration();
	int formulation_day = mission->get_formulation_day();
	int target_location = mission->get_target_location();

	cout << mission_type << "  " << mission_duration << "  " << formulation_day << "  " << target_location<<endl;

}
