#pragma once
#include "Event.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/List ADT/LinkedList.h"
#include "../Misc/Station.h"

class CancellationEvent : public Event {
private:

public:
	CancellationEvent(sint32 M_ID, sint32 Event_Day, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m);
	void Execute();
	bool CancelMission(int id, Mission*& mission);
	~CancellationEvent();
};