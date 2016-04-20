#include "ID.h"

void ID::signals_in(const IFID& ifid, const Controls& ctrl, uint8_t write_reg, uint16_t write_data, bool stall)
{
	_controls = ctrl;
	_ifid = ifid;

	uint8_t read1;
	uint8_t read2;
	if(!ctrl.id_controls.use_8bit_data) {
		read1 = (ifid.instruction >> 4) & 0x000F;
		read2 = (ctrl.id_controls.reg_position
			? ifid.instruction >> 0
			: ifid.instruction >> 8) & 0x000F;
	}
	else {
		read1 = read2 = 0;
	}

	// TODO this signal is redundant
	const bool write = (write_reg != 0);

	_register_file.signals_in(read1, read2, write, write_reg, write_data);
}

void ID::tick()
{
	_register_file.tick();

	recompute_signals_out();
	recompute_new_pc_address_out();
}

void ID::tock()
{
	_register_file.tock();
}

IDEX ID::signals_out() const
{
	return _signals_out;
}

uint16_t ID::new_pc_address_out() const
{
	return _new_pc_address_out;
}

void ID::recompute_signals_out()
{
	const uint8_t write_reg = _controls.id_controls.reg_write
		? (_controls.id_controls.reg_position
		   ? _ifid.instruction >> 8
		   : _ifid.instruction) & 0x000F
		: 0;

	uint16_t write_data;
	if(_controls.id_controls.use_8bit_data) {
		const uint8_t write_data_bits = (_ifid.instruction >> 4) & 0x00FF;
		write_data = write_data_bits >= 0x80
			? write_data_bits | 0xFF00
			: write_data_bits;
	}
	else {
		const uint8_t write_data_bits = (_ifid.instruction >> 8) & 0x000F;
		write_data = write_data_bits >= 0x8
			? write_data_bits | 0xFFF0
			: write_data_bits;
	}

	_signals_out = {
		_controls.ex_controls,
		_controls.mem_controls,
		_controls.wb_controls,

		_register_file.data1_out(),
		_register_file.data2_out(),

		0, // branch_offset

		write_reg,
		write_data,
	};
}

void ID::recompute_new_pc_address_out()
{
	// Get the offset nybble, shift it left, and sign-extend it.
	const uint8_t offset_bits = (_ifid.instruction << 1) & 0x000F;
	const int8_t offset = offset_bits >= 0x08 ? offset_bits | 0xF0 : offset_bits;

	if(_controls.id_controls.jump) {
		_new_pc_address_out = (_ifid.pc_plus_2 & 0xF000) | ((_ifid.instruction & 0x0FFF) << 1);
	}
	else if(_controls.id_controls.branch_z &&
	        _register_file.data1_out() == _register_file.data2_out()) {
	    _new_pc_address_out = _ifid.pc_plus_2 + offset;
	}
	else if(_controls.id_controls.branch_lt &&
	        _register_file.data1_out() < _register_file.data2_out()) {
	    _new_pc_address_out = _ifid.pc_plus_2 + offset;
	}
	else {
		_new_pc_address_out = _ifid.pc_plus_2;
	}
}
