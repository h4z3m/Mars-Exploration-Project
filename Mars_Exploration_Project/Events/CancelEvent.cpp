#include "CancelEvent.h"
#include "../Missions/Mission.h"


CancellationEvent::CancellationEvent(sint32 M_ID, sint32 Event_Day, LinkedQueue<Mission*>& p_m, PriQ<Mission*>& e_m, LinkedList<Mission*>& m_m) : Event(M_ID, Event_Day, p_m, e_m, m_m) 
{
}

bool CancellationEvent::CancelMission(int id, Mission*& mission)
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
void CancellationEvent::Execute() {
	Mission* misson = NULL;
	CancelMission(Mission_ID, misson);
}

CancellationEvent::~CancellationEvent() {}