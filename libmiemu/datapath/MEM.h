#ifndef MEM_H
#define MEM_H

#include "signals.h"

class MEM {
public:
	void signals_in(const EXMEM&);
	void tick();
	void tock();
	MEMWB signals_out() const;
};

#endif
