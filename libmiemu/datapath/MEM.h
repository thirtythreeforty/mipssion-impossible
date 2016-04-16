#ifndef MEM_H
#define MEM_H

#include "signals.h"
#include "../program_memory.h"

class MEM {

public:
	EXMEM _exmem;
	MEMWB _signals_out;

	void signals_in(const EXMEM&);
	void tick(const Memory&);
	void tock(Memory&);
	MEMWB signals_out() const;
};

#endif
