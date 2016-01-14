#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm> // sort
#include <stdio.h>
#include "Pocket.h"

class Queue
{
public:
	Queue();
	~Queue();

	void PushPocket(Pocket* pk);
	Pocket* PullPocket();
	int getSize();
private:
	std::vector<Pocket*> pks;
};

#endif
