#include "IF.h"

void IF::set_pc(uint16_t _pc)
{
	// For tests and debugging only
	program_counter = _pc;
}

uint16_t IF::get_pc() const
{
	return program_counter;
}

void IF::signals_in(uint16_t new_pc_address, const IFControls& controls, bool stall)
{
	_stall = stall;
	if (!stall)
	{
		if (controls.use_new_address)
			IF::program_counter = new_pc_address;
		else
			program_counter = signals_o.pc_plus_2;
	}
}

void IF::tick(const Memory& mem)
{
	if (!_stall) {
		signals_o.instruction = mem.get(program_counter);
		program_counter += 2;
		signals_o.pc_plus_2 = program_counter;
	}
}

void IF::tock(const Memory&)
{
}

IFID IF::signals_out() const
{
	return signals_o;
}
