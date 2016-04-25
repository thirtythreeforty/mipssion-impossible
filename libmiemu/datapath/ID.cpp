#include "ID.h"

void ID::signals_in(const IFID& ifid, const Controls& ctrl, uint8_t write_reg, uint16_t write_data, FRWD_Out fwdout, bool stall)
{
	_fwdout = fwdout;

	_controls = ctrl;
	_ifid = ifid;
	_stall = stall;
	
	if(ctrl.id_controls.jump_link) {
		read1 = 14; // link register
		read2 = 0;
	}
	else if(!ctrl.id_controls.use_8bit_data) {
		read1 = (ifid.instruction >> 4) & 0x000F;
		read2 = (ctrl.id_controls.reg_position
			? ifid.instruction >> 0
			: ifid.instruction >> 8) & 0x000F;
	}
	else { // use_8bit_data == true
		read1 = read2 = 0;
	}

	// TODO this signal is redundant
	const bool write = (write_reg != 0);

	_register_file.signals_in(read1, read2, write, write_reg, write_data);

	recompute_signals_out();
	recompute_new_pc_address_out();
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

	recompute_signals_out();
	recompute_new_pc_address_out();
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
	uint8_t write_reg;

	if (_controls.id_controls.reg_write) {
		write_reg = (_controls.id_controls.reg_position
			? _ifid.instruction >> 8
			: _ifid.instruction) & 0x000F;
	}
	else if (_controls.id_controls.write_link) {
		write_reg = 14; // link register
	}
	else {
		write_reg = 0;
	}

	uint16_t write_data;
	if (_controls.id_controls.write_link) {
		write_data = _ifid.pc_plus_2;
	}
	else if (_controls.id_controls.use_8bit_data) {
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

	switch (_fwdout.REGSRC1) {
	case 0:
		data1 = _register_file.data1_out();
		break;
	case 1:
		data1 = _fwdout.exmem_alu_output;
		break;
	case 2:
		data1 = _fwdout.memwb_data;
		break;
	}
	switch (_fwdout.REGSRC2) {
	case 0:
		data2 = _register_file.data2_out();
		break;
	case 1:
		data2 = _fwdout.exmem_alu_output;
		break;
	case 2:
		data2 = _fwdout.memwb_data;
		break;
	}

	if (_stall) {
		_signals_out = {
			{},
			{},
			{},

			0,
			0,

			0,
			0,

			0, // branch_offset

			0,
			0,
		};
	}
	else {
		_signals_out = {
			_controls.ex_controls,
			_controls.mem_controls,
			_controls.wb_controls,
			read1,
			read2,

			data1,
			data2,

			0, // branch_offset

			write_reg,
			write_data,
		};
	}
}

void ID::recompute_new_pc_address_out()
{
	// Get the offset nybble, shift it left, and sign-extend it.
	const uint8_t offset_bits = (_ifid.instruction << 1) & 0x000F;
	const int8_t offset = offset_bits >= 0x08 ? offset_bits | 0xF0 : offset_bits;

	if(_controls.id_controls.jump) {
		_new_pc_address_out = (_ifid.pc_plus_2 & 0xF000) | ((_ifid.instruction & 0x0FFF) << 1);
	}
	else if(_controls.id_controls.jump_link) {
		_new_pc_address_out = _register_file.data1_out();
	}
	else if(_controls.id_controls.branch_z &&
	       data1 == data2) {
	    _new_pc_address_out = _ifid.pc_plus_2 + offset;
	}
	else if(_controls.id_controls.branch_lt &&
	        data1 < data2) {
	    _new_pc_address_out = _ifid.pc_plus_2 + offset;
	}
	else {
		_new_pc_address_out = _ifid.pc_plus_2;
	}
}
