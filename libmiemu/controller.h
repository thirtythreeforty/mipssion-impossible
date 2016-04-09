#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datapath/signals.h"

#define ADDI 0000
#define ADD 0001
#define SUB 0010
#define AND 0011
#define OR 0100
#define XOR 0101
#define SLL 0110
#define SRL 0111
#define BLT 1000
#define J 1001
#define JL 1010
#define JR 1011
#define BEQ 1100
#define LW 1101
#define SW 1110
#define LBI 1111

#define DONT_CARE 0

class Controller
{
	uint16_t _instruction;
	uint8_t _opcode;

public:
	void signals_in(uint16_t instruction);
	Controls controls_out() const;
};

#endif
