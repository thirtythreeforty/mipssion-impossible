#ifndef DATAPATH_H
#define DATAPATH_H

#include "program_memory.h"

#include "datapath/IF.h"
#include "datapath/ID.h"
#include "datapath/EX.h"
#include "datapath/MEM.h"
#include "datapath/WB.h"

#include "datapath/signals.h"

class Datapath
{
	Memory _memory;

	IF _IF;
	IFID _IFID;
	ID _ID;
	IDEX _IDEX;
	EX _EX;
	EXMEM _EXMEM;
	MEM _MEM;
	MEMWB _MEMWB;
	WB _WB;

public:
	void control_signals_in(const Controls&);
	void tick(Memory& memory);
	void tock(Memory& memory);
	ControlInputs control_inputs_out() const;
};

#endif
