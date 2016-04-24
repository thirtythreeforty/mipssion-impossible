#ifndef IF_H
#define IF_H

#include <cstdint>

#include "../program_memory.h"

#include "signals.h"

class IF
{
	uint16_t program_counter = 0;
	IFID signals_o;
	bool _stall = 0;

public:
	void set_pc(uint16_t);
	uint16_t get_pc() const;

	void signals_in(uint16_t new_pc_address, const IFControls& controls, bool stall);
	void tick(const Memory&);
	void tock(const Memory&);
	IFID signals_out() const;
};

#endif
