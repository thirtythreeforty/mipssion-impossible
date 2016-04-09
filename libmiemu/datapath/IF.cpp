#include "IF.h"

void IF::set_pc(uint16_t)
{
	// For tests and debugging only
}

uint16_t IF::get_pc() const
{
	return 0;
}

void IF::signals_in(uint16_t new_pc_address, const IFControls& controls)
{
}

void IF::tick(const Memory&)
{
}

void IF::tock(const Memory&)
{
}

IFID IF::signals_out() const
{
	return {};
}
