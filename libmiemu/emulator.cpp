#include "libmiemu.h"

void Emulator::step()
{
	bool stall = false;
	_controller.signals_in(_datapath.control_inputs_out());
	stall = _hazard.run_hazard_unit(_datapath.get_IFID(), _datapath.get_IDEX(), _datapath.get_EXMEM(), _datapath.get_MEMWB());
	_datapath.control_signals_in(_controller.controls_out(), stall);

	_datapath.tick(_memory);
	_datapath.tock(_memory);
}
