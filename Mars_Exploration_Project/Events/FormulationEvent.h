#pragma once
#include "Event.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/List ADT/LinkedList.h"
class FormulationEvent : public Event {
private:
	sint8  MissionType;
	sint32 TargetLoc;
	sint32 MissionDuration;
	sint8  MissionSignificance;
public:
	FormulationEvent();
	FormulationEvent(sint8 mType, sint32 eDay, sint32 id, sint32 loc, sint32 dur, sint8 sig, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m);
	void Execute();
	sint8 getMissionType();

	~FormulationEvent();
};