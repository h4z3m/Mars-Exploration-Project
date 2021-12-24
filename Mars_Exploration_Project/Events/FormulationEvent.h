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
	FormulationEvent(sint8 mType, sint32 eDay, sint32 id, sint32 loc, sint32 dur, sint8 sig);

	void Execute(LinkedQueue<Mission*> & P_Missions);
	void Execute(PriQ<Mission*>& E_Missions);
	void Execute(LinkedList<Mission*>& M_Missions);
	sint8 getMissionType();

	~FormulationEvent();
};