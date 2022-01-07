#include "PromotionEvent.h"
#include "../Missions/Mission.h"

PromotionEvent::PromotionEvent(sint32 M_ID, sint32 Event_Day, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m) :Event(M_ID, Event_Day,p_m,e_m,m_m)
{

}

void PromotionEvent::Execute()
{
	Mission* temp = NULL;
	DeleteFromMountList(Mission_ID, temp);

	if (temp)
	{
		temp->set_mission_type(EMERGENCY);
		AddToEmergencyList(temp, temp->get_significance());
	}
}
//so that i use it in both cancellation & promotion events
bool PromotionEvent::DeleteFromMountList(int id, Mission*& mission)
{
	int i = 1;
	Mission* temp = NULL;
	while (!M_Missions->isEmpty())
	{
		temp = M_Missions->getEntry(i);
		if (temp)
		{
			if (temp->get_id() == id)
			{
				mission = temp;
				break;
			}
		}
		else
			break;
		i++;
	}

	if (mission != nullptr) {
		M_Missions->remove(i);
		return true;
	}

	else
		return false;

}

void PromotionEvent::AddToEmergencyList(Mission* mission, int priority)
{
	E_Missions->enqueue(mission, priority);
}

PromotionEvent::~PromotionEvent()
{
}
