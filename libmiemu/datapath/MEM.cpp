#include "MEM.h"

void MEM::signals_in(const EXMEM& exmem)
{
	_exmem = exmem;
	_signals_out.alu_output = _exmem.alu_output;
	_signals_out.wb_controls = _exmem.wb_controls;
	_signals_out.write_reg = _exmem.write_reg;
}

void MEM::tick(const Memory& mem)
{
	_signals_out.memory_data = mem.get_datapath(_exmem.alu_output);
}

void MEM::tock(Memory& mem)
{
	if (_exmem.mem_controls.mem_write)
	{
		mem.set_datapath(_exmem.alu_output, _exmem.write_data);
	}
}

MEMWB MEM::signals_out() const
{
	return _signals_out;
}
