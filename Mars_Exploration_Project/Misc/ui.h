#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <chrono>
#include <thread>
#include "common_types.h"
#include "../Missions/Mission.h"
#include "../Rovers/Polar_Rover.h"

#define CLEAR_STR(name) name.str("");name.clear()
using namespace std;
class UI {
private:
public:
	void UI_printString(const char *st);
	void UI_printStringColor(const char* COLOR_CODE,stringstream& msg);
	string UI_getString();
	char UI_getChar();
	void print_rover_info(Rover *r);
	void print_mission_info(Mission *m);
	void UI_WaitKeyPress();
	void UI_DelaySeconds(int sec);
	void UI_clear_screen();
};