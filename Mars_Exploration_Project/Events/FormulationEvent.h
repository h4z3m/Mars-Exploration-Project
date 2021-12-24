#include "Event.h"
class FormulateEvent : public Event {
private:
	uint8  MissionType;
	uint32 TargetLoc;
	uint32 MissionDuration;
	uint8  MissionSignificance;
public:
	FormulateEvent();
	FormulateEvent(uint8 mType, uint32 eDay, uint32 id, uint32 loc, uint32 dur, uint8 sig);
	void Execute();
	~FormulateEvent();
};