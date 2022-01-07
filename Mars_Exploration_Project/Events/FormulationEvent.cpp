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
void FormulationEvent::Execute(Station* S)
{

}



sint8 FormulationEvent::getMissionType()
{
	return MissionType;
}

FormulationEvent::~FormulationEvent()
{
}
