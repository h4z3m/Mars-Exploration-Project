#include"FormulationEvent.h"
#include "../Missions/Mission.h"
FormulationEvent::FormulationEvent()
{
}
FormulationEvent::FormulationEvent(sint8 mType, sint32 eDay, sint32 id, sint32 loc, sint32 dur, sint8 sig) : Event(id, eDay)
{
	MissionType = mType;
	TargetLoc = loc;
	MissionDuration = dur;
	MissionSignificance = sig;
}
//Polar missions only
void FormulationEvent::Execute(LinkedQueue<Mission*>& P_Missions)
{
	Mission* newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance,Mission_ID);
	P_Missions.enqueue(newM);
}

void FormulationEvent::Execute(PriQ<Mission*>& E_Missions)
{
	Mission* newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance,Mission_ID);
	E_Missions.enqueue(newM, MissionSignificance);
}
void FormulationEvent::Execute(LinkedList<Mission*>& M_Missions)
{
	Mission* newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance, Mission_ID);
	M_Missions.InsertBeg(newM);
}

sint8 FormulationEvent::getMissionType()
{
	return MissionType;
}

FormulationEvent::~FormulationEvent()
{
}
