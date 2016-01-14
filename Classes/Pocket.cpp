#include "Pocket.h"
//#include "Util.h"

Pocket::Pocket():length(0),version(0),id(0),msg(NULL){

}

Pocket::~Pocket()
{
	if (msg != NULL) {
		delete[] msg;
	}
}

