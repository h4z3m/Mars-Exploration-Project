#include"FormulationEvent.h"
#include "../Missions/Mission.h"
#include "../Datastructures/List ADT/LinkedList.h"
#include "../Datastructures/PriQ ADT/PriQ.h"
#include "../Datastructures/Queue ADT/LinkedQueue.h"
FormulationEvent::FormulationEvent()
{
}
FormulationEvent::FormulationEvent(sint8 mType, sint32 eDay, sint32 id, sint32 loc, sint32 dur, sint8 sig, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m) : Event(id, eDay, p_m, e_m , m_m)
{
	MissionType = mType;
	TargetLoc = loc;
	MissionDuration = dur;
	MissionSignificance = sig;
}
void FormulationEvent::Execute(Station* S)
{
	switch (MissionType) {
		case 'P':
			Mission * newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance, Mission_ID);
			P_Missions.enqueue(newM);
			break;
		case 'E':
			Mission * newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance, Mission_ID);
			E_Missions.enqueue(newM, MissionSignificance);
			break;
		case 'M':
			Mission * newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance, Mission_ID);
			M_Missions.InsertBeg(newM);
			break;
	}
}

sint8 FormulationEvent::getMissionType()
{
	return MissionType;
}

FormulationEvent::~FormulationEvent()
{
}
