#include "Queue.h"

//pthread_mutex_t MsgQueue::lock;
Queue::Queue()
{
}

Queue::~Queue()
{
}

void Queue::PushPocket(Pocket* pk)
{
	pks.push_back(pk);
}

Pocket* Queue::PullPocket()
{
	Pocket* pk=nullptr;
	
	if (pks.size() > 0)
	{
		pk = *(pks.begin());
		pks.erase(pks.begin());
		//pk = pks.begin();
	}
	return pk;
}

int Queue::getSize()
{
	return pks.size();
}