#ifndef ALU_H
#define ALU_H

#include <cstdint>

#include "signals.h"

class ALU
{
	ALUOp _op;
	uint16_t _data1;
	uint16_t _data2;

	uint16_t _output;
public:
	void signals_in(ALUOp, uint16_t data1, uint16_t data2);
	void tick();
	void tock();

	uint16_t data_out();
	bool z_out();
	bool c_out();
};

#endif
