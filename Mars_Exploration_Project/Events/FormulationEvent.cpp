#include"FormulationEvent.h"
#include "../Missions/Mission.h"
FormulateEvent::FormulateEvent(uint8 mType, uint32 eDay, uint32 id, uint32 loc, uint32 dur, uint8 sig) : Event(id, eDay)
{
	MissionType = mType;
	TargetLoc = loc;
	MissionDuration = dur;
	MissionSignificance = sig;
}

void FormulateEvent::Execute()
{
	Mission* newM = new Mission(MissionType, Event_Day, TargetLoc, MissionDuration, MissionSignificance);
	
}

FormulateEvent::~FormulateEvent()
{
}
