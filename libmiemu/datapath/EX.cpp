#include "EX.h"
#include <iostream>

void EX::signals_in(const IDEX& idex)
{
	_idex = idex;
	_excontrols = idex.ex_controls;
	uint16_t _data2;

	std::cout << "ALU INPUT 1 IS " << _idex.data1 << std::endl;
	std::cout << "ALU INPUT 2 IS " << _idex.data2 << std::endl;


	if (_idex.ex_controls.alu_src == 0) {
		std::cout << "HERE 1" << std::endl;
		_data2 = _idex.data2;
	}
	
	if (_excontrols.alu_src == 1) {
		std::cout << "HERE 2" << std::endl;
		_data2 = _idex.branch_offset;
	}
	
	
	_alu.signals_in(_excontrols.alu_op, _idex.data1, _data2);
	

}

void EX::tick()
{
	_alu.tick();

	compute_signals_out();
}

void EX::tock()
{
	_alu.tock();
}

EXMEM EX::signals_out() const
{
	return _signals_out;
}

void EX::compute_signals_out() {

	MEMControls _mem_controls = _idex.mem_controls;
	WBControls _wb_controls = _idex.wb_controls;

	uint16_t _alu_output = _alu.data_out();
	uint16_t _write_data = _idex.data2;

	uint8_t _write_reg = _idex.write_reg;
	_signals_out = {_mem_controls, _wb_controls, _alu_output, _write_data, _write_reg};
}
