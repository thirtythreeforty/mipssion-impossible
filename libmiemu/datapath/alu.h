#ifndef ALU_H
#define ALU_H

#include <cstdint>

#include "signals.h"

class ALU
{
public:
	void signals_in(ALUOp, uint16_t data1, uint16_t data2);
	void tick();
	void tock();

	uint16_t data_out();
	bool z_out();
	bool c_out();
};

#endif
