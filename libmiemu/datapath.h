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

	const IF& get_IF() const { return _IF; }
	const IFID& get_IFID() const { return _IFID; }
	const ID& get_ID() const { return _ID; }
	const IDEX& get_IDEX() const { return _IDEX; }
	const EX& get_EX() const { return _EX; }
	const EXMEM& get_EXMEM() const { return _EXMEM; }
	const MEMWB& get_MEMWB() const { return _MEMWB; }
	const WB& get_WB() const { return _WB; }
};

#endif
