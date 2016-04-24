#ifndef FORWARD_H
#define FORWARD_H

#include "signals.h"
#include <utility>
#include "../instructions.h"

class Forward
{
private:

	uint8_t _exmem_rd;
	uint8_t _memwb_rd;
	uint8_t _idex_rs;
	uint8_t _idex_rt;

	uint16_t _exmem_output;
	uint16_t _memwb_output;

	FRWD_Out _fwd;

	std::pair<uint8_t, uint8_t> Forward::getRead(uint16_t _instruction, uint8_t _op);
	uint8_t _opcode;
	uint16_t _instruct;

public:
	void signals_in(const IFID&, const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	FRWD_Out signals_out() const;
	FRWD_Out run_forwarding_unit(const IFID& ifid, const IDEX&, const EXMEM&, const MEMWB&);

	std::pair<uint8_t, uint8_t> readRegs;
};
#endif // !FORWARD_H
