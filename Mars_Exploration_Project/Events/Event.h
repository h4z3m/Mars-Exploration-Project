#pragma once
#include "../Misc/common_types.h"
#include "../Missions/Mission.h"
#include "../Misc/Station.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/List ADT/LinkedList.h"
class Event {
protected:
	sint32 Mission_ID;
	sint32 Event_Day;

	LinkedQueue<Mission*> P_Missions;
	PriQ<Mission*> E_Missions;
	LinkedList<Mission*> M_Missions;

public:
	Event() {}
	Event(sint32 id,sint32 day,LinkedQueue<Mission*>& p_m,PriQ<Mission*>& e_m,LinkedList<Mission*>& m_m) {
		Mission_ID = id;
		Event_Day = day;

		P_Missions = p_m;
		E_Missions = e_m;
		M_Missions = m_m;
	}
	uint32 getEventDay() {
		return Event_Day;
	}
	virtual void Execute(Station* S) = 0;

	virtual sint8 getMissionType() = 0;

};