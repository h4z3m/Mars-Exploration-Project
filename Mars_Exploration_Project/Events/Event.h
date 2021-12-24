#pragma once
#include "../Misc/common_types.h"
#include "../Missions/Mission.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/List ADT/LinkedList.h"
class Event {
protected:
	sint32 Mission_ID;
	sint32 Event_Day;
public:
	Event() {}
	Event(sint32 id,sint32 day) {
		Mission_ID = id;
		Event_Day = day;
	}
	uint32 getEventDay() {
		return Event_Day;
	}
	virtual void Execute(PriQ<Mission*> & P_Missions) = 0;
	virtual void Execute(LinkedQueue<Mission*>& E_Missions) = 0;
	virtual void Execute(LinkedList<Mission*>& M_Missions) = 0;

	virtual sint8 getMissionType() = 0;

};