#include "libmiemu.h"

void Emulator::step()
{
	bool stall = false;
	_controller.signals_in(_datapath.control_inputs_out());
	_fwdout = _fwd.run_forwarding_unit(_datapath.get_IFID(), _datapath.get_IDEX(), _datapath.get_EXMEM(), _datapath.get_MEMWB());
	stall = _hazard.run_hazard_unit(_datapath.get_IFID(), _datapath.get_IDEX(), _datapath.get_EXMEM(), _datapath.get_MEMWB());
	_datapath.control_signals_in(_controller.controls_out(), _fwdout, stall);

	
	_datapath.tick(_memory);
	_datapath.tock(_memory);
}
