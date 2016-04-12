#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "datapath/signals.h"



class Controller
{
	uint8_t _opcode;

public:
	void signals_in(uint16_t instruction);
	Controls controls_out() const;
};

#endif
