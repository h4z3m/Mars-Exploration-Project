#include "PromotionEvent.h"
#include "../Missions/Mission.h"

PromotionEvent::PromotionEvent(sint32 M_ID, sint32 Event_Day) :Event(M_ID, Event_Day)
{

}

void PromotionEvent::Execute(Station* S)
{
	Mission* temp = NULL;
	S->DeleteFromMountList(Mission_ID, temp);

	if (temp)
	{
		temp->set_mission_type(EMERGENCY);
		S->AddToEmergencyList(temp, temp->get_significance());
	}
}


PromotionEvent::~PromotionEvent()
{
}
