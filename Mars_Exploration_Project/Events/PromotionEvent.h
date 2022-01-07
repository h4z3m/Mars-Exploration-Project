#pragma once
#include "Event.h"
#include "../Misc/Station.h"

class PromotionEvent : public Event
{
public:
	PromotionEvent(sint32 M_ID, sint32 Event_Day);
	void Execute(Station* S);

	 ~PromotionEvent();
};
