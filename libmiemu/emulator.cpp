#include "libmiemu.h"

void Emulator::step()
{
	_controller.signals_in(_datapath.control_inputs_out());
	_datapath.control_signals_in(_controller.controls_out());

	_datapath.tick(_memory);
	_datapath.tock(_memory);
}
