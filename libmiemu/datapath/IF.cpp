#include "IF.h"

void IF::set_pc(uint16_t)
{
	// For tests and debugging only
}

uint16_t IF::get_pc() const
{
	return program_counter;
}

void IF::signals_in(uint16_t new_pc_address, const IFControls& controls, bool stall)
{
	if(controls.use_new_address)
		IF::program_counter = new_pc_address;
	
}

void IF::tick(const Memory& mem)
{
	signals_o.instruction = mem.get(IF::get_pc());
	program_counter = IF::get_pc() + 2;
	signals_o.pc_plus_2 = program_counter;
}

void IF::tock(const Memory&)
{
}

IFID IF::signals_out() const
{
	return signals_o;
}
