#ifndef EX_H
#define EX_H

#include "signals.h"
#include "alu.h"

class EX
{
	ALU _alu;

public:
	void signals_in(const IDEX&);
	void tick();
	void tock();
	EXMEM signals_out() const;
};

#endif
