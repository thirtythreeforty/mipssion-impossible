#include "forwarding.h"


void Forward::signals_in(const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb)
{
	_exmem_rd = exmem.write_reg;
	_memwb_rd = memwb.write_reg;

	_exmem_output = exmem.alu_output;
	_memwb_output = memwb.memory_data;

	_idex_rs = idex.read1;
	_idex_rt = idex.read2;

}

void Forward::tick()
{
	//rs = exem rd
	//rt = exmem rd
	//rs = memwb rd
	//rt = memwb rd

	//RS
	if (_idex_rs == _exmem_rd) {
		_fwd.ALUSRC1 = 1;
		_fwd.exmem_alu_output = _exmem_output;
	}
	else if (_idex_rs == _memwb_rd) {
		_fwd.ALUSRC1 = 2;
		_fwd.memwb_data = _memwb_output;
	}
	else {
		_fwd.ALUSRC1 = 0;
	}


	//RT
	if (_idex_rt == _exmem_rd) {
		_fwd.ALUSRC2 = 1;
		_fwd.exmem_alu_output = _exmem_output;
	}
	else if (_idex_rt == _memwb_rd) {
		_fwd.ALUSRC2 = 2;
		_fwd.memwb_data = _memwb_output;
	}
	else {
		_fwd.ALUSRC2 = 0;
	}
}

void Forward::tock()
{
}

FRWD_Out Forward::signals_out() const
{
	return _fwd;
}

FRWD_Out Forward::run_forwarding_unit (const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb) {
	Forward::signals_in(idex, exmem, memwb);
	Forward::tick();
	Forward::tock();
	return Forward::signals_out();
}