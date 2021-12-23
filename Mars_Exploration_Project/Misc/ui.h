#include <string>
#include <iostream>
#include "../Missions/Mission.h"
#include "../Rovers/Polar_Rover.h"
using namespace std;
class UI {
private:


public:

	void UI_printString(const char *st);
	string UI_getString();
	char UI_getChar();
	void UI_Interactive_Mode(void);
	void UI_Step_By_Step(void);
	void UI_Silent_Mode(void);
	void print_rover_info(Rover *r);
	void print_mission_info(Mission *m);

};