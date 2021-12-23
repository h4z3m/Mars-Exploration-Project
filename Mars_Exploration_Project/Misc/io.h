#include "../Datastructures/PriQ ADT/PriQ.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class IO {
private:
	ifstream file;
	string fileName;
public:
	typedef int Event;

	IO();
	bool IO_ReadFile(PriQ<Event> *& ReturnList);
	bool IO_OutputFile(PriQ<Event> *& OutputList );
	~IO();
};