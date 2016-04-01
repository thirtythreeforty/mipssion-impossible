#ifndef IF_H
#define IF_H

#include <cstdint>

#include "../program_memory.h"

#include "signals.h"

class IF
{
	uint16_t program_counter;

public:
	void set_pc(uint16_t);
	uint16_t get_pc() const;

	void signals_in(uint16_t new_pc_address);
	void tick(const Memory&);
	void tock(const Memory&);
	IFID signals_out() const;
};

#endif
