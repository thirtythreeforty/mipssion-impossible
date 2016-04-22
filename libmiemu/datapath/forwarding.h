#ifndef FORWARD_H
#define FORWARD_H

#include "signals.h"

class Forward
{
private:
	uint16_t _exmem_rd;
	uint16_t _memwb_rd;
	uint16_t _idex_rs;
	uint16_t _idex_rt;

	uint16_t _exmem_output;
	uint16_t _memwb_output;

	FRWD_Out _fwd;

public:
	void signals_in(const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	FRWD_Out signals_out() const;
};
#endif // !FORWARD_H
