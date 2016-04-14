#include "WB.h"

void WB::signals_in(const MEMWB& memwb)
{
	write_data = memwb.wb_controls.mem_to_reg
		? memwb.memory_data
		: memwb.alu_output;
	write_reg = memwb.write_reg;
}

uint8_t WB::write_reg_out() const
{
	return write_reg;
}

uint16_t WB::write_data_out() const
{
	return write_data;
}
