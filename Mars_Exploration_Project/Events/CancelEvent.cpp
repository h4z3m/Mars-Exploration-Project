#include "CancelEvent.h"
#include "../Missions/Mission.h"


CancellationEvent::CancellationEvent(sint32 M_ID, sint32 Event_Day) : Event(M_ID, Event_Day) {

}

void CancellationEvent::Execute(Station* S) {
	Mission* misson = NULL;
	S->DeleteFromMountList(Mission_ID, misson);
}

CancellationEvent::~CancellationEvent() {}