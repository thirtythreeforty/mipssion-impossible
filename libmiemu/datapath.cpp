#include "datapath.h"

void Datapath::control_signals_in(const Controls& controls)
{
	// This is tricky -- the combinatorial signals must be propagated
	// correctly.  This is easy in actual hardware but the right order must be
	// preserved here.  We have these combinatorial signals (-> here means
	// "depends on", and * means a register (which does not depend on
	// anything)).  They are in dependency order: basically a module cannot
	// appear on the right unless it has first appeared on the left, or is a
	// register, which keep their own state.
	//     WB -> MEMWB*
	//     ID -> WB, IFID*, controls
	//     IF -> ID
	//     MEM -> EXMEM*
	//     EX -> IDEX*
	// So here is that pattern.

	_WB.signals_in(_MEMWB);
	_ID.signals_in(_IFID, controls, _WB.write_reg_out(), _WB.write_data_out());
	_IF.signals_in(_ID.new_pc_address_out(), controls.if_controls);
	//_EX.signals_in(...);
	_MEM.signals_in(_EXMEM);
}

void Datapath::tick(Memory& memory)
{
	_IF.tick(memory);
	_ID.tick();
	// _EX.tick();
	_MEM.tick(memory);
}

void Datapath::tock(Memory& memory)
{
	_IF.tock(memory);
	_ID.tock();
	// EX.tock();
	_MEM.tock(memory);

	// At this point the registers get filled
	_IFID = _IF.signals_out();
	_IDEX = _ID.signals_out();
	// _EXMEM = _EX.signals_out();
	_MEMWB = _MEM.signals_out();
}

ControlInputs Datapath::control_inputs_out() const
{
	return ControlInputs{
		_IF.signals_out().instruction
	};
}
