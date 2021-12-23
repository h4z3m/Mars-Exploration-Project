#include "UI.h"

void UI::UI_printString(const string &st)
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
