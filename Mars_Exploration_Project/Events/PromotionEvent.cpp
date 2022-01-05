#include "PromotionEvent.h"
#include "../Missions/Mission.h"


PromotionEvent::PromotionEvent(sint32 M_ID, sint32 Event_Day) : Event(M_ID, Event_Day) {

}

void PromotionEvent::Execute(Station* S) {

	Mission* temp = S->GetRequestedMission(Mission_ID);

	S->CancelMission(Mission_ID);

	temp->set_mission_type('E');

	S->AddEmergencyMission(temp, temp->get_significance());



	




}

PromotionEvent::~PromotionEvent() {}