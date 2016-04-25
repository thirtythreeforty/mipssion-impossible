#ifndef EX_H
#define EX_H

#include "signals.h"
#include "alu.h"

class EX
{
	ALU _alu;
	EXMEM _signals_out;

public:
	void signals_in(const IDEX&, FRWD_Out);
	void tick();
	void tock();
	EXMEM signals_out() const;

private:
	IDEX _idex;
	EXControls _excontrols;
	void compute_signals_out();
	
};

#endif
