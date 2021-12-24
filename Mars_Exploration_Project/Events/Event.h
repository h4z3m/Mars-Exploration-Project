#pragma once
#include "../Misc/common_types.h"
class Event {
protected:
	uint32 Mission_ID;
	uint32 Event_Day;
public:
	Event() {}
	Event(uint32 id,uint32 day) {
		Mission_ID = id;
		Event_Day = day;
	}
	virtual void Execute() = 0;
};