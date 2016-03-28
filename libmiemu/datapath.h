#ifndef DATAPATH_H
#define DATAPATH_H

#include "datapath/IF.h"

class Datapath
{
	IF _instruction_fetch;

	void tick();
	void tock();
};

#endif
