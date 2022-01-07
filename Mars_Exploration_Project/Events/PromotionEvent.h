#pragma once
#include "Event.h"


class PromotionEvent : public Event
{
public:
	PromotionEvent(sint32 M_ID, sint32 Event_Day, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m);
	void Execute();
	bool DeleteFromMountList(int id, Mission*& mission);
	void AddToEmergencyList(Mission* mission, int priority);

	 ~PromotionEvent();
};
