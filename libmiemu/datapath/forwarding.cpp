#include "forwarding.h"


void Forward::signals_in(const IFID& ifid, const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb)
{
	_exmem_rd = exmem.write_reg;
	_memwb_rd = memwb.write_reg;

	_exmem_output = exmem.alu_output;
	if (memwb.wb_controls.mem_to_reg == 1)
		_memwb_output = memwb.memory_data;
	else
		_memwb_output = memwb.alu_output;

	_idex_rs = idex.read1;
	_idex_rt = idex.read2;

	_opcode = (ifid.instruction & 0xF000) >> 12;
	//rs rt
	readRegs = getRead(ifid.instruction, _opcode);

}

void Forward::tick()
{
	//rs = exem rd
	//rt = exmem rd
	//rs = memwb rd
	//rt = memwb rd

	//RS
	if (_idex_rs == _exmem_rd
		&& _exmem_rd != 0) {
		_fwd.ALUSRC1 = 1;
		_fwd.exmem_alu_output = _exmem_output;
	}
	else if (_idex_rs == _memwb_rd
		&& _memwb_rd != 0) {
		_fwd.ALUSRC1 = 2;
		_fwd.memwb_data = _memwb_output;
	}
	else {
		_fwd.ALUSRC1 = 0;
	}


	//RT
	if (_idex_rt == _exmem_rd
		&& _exmem_rd != 0) {
		_fwd.ALUSRC2 = 1;
		_fwd.exmem_alu_output = _exmem_output;
	}
	else if (_idex_rt == _memwb_rd
		&& _memwb_rd != 0) {
		_fwd.ALUSRC2 = 2;
		_fwd.memwb_data = _memwb_output;
	}
	else {
		_fwd.ALUSRC2 = 0;
	}
	//Branches
	if (_opcode == op::blt || _opcode == op::beq) {
			//rs
			if (_exmem_rd == readRegs.first && _exmem_rd != 0) {
				_fwd.REGSRC1 = 1;
				_fwd.exmem_alu_output = _exmem_output;
			}
			else if (_memwb_rd == readRegs.first && _memwb_rd != 0) {
				_fwd.REGSRC1 = 2;
				_fwd.memwb_data = _memwb_output;
			}
			else {
				_fwd.REGSRC1 = 0;
			}
			//rt
			if (_exmem_rd == readRegs.second && _exmem_rd != 0) {
				_fwd.REGSRC2 = 1;
				_fwd.exmem_alu_output = _exmem_output;
			}
			else if (_memwb_rd == readRegs.second && _memwb_rd != 0) {
				_fwd.REGSRC2 = 2;
				_fwd.memwb_data = _memwb_output;

			}
			else {
				_fwd.REGSRC2 = 0;
			}

	}
	else
	{
		_fwd.REGSRC1 = _fwd.REGSRC2 = 0;
	}
		
}

void Forward::tock()
{
}

FRWD_Out Forward::signals_out() const
{
	return _fwd;
}

FRWD_Out Forward::run_forwarding_unit (const IFID& ifid, const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb) {
	Forward::signals_in(ifid, idex, exmem, memwb);
	Forward::tick();
	Forward::tock();
	return Forward::signals_out();
}

std::pair<uint8_t, uint8_t> Forward::getRead(uint16_t _instruction, uint8_t _op)
{
	switch (_op)
	{
		//Use reg position 1, to get read reg 2
	case op::add:
	case op::sub:
	case op::and_:
	case op::or_:
	case op::xor_:
	case op::sll:
	case op::srl:
		return std::make_pair((_instruction >> 4) & 0x000F, (_instruction >> 0) & 0x000F);
		break;
		//Use reg position 0, to get read reg 2
	case op::addi:
	case op::blt:
	case op::beq:
	case op::lw:
	case op::sw:
		return std::make_pair((_instruction >> 4) & 0x000F, (_instruction >> 8) & 0x000F);
		break;
		//These instructions do not read from regs
	case op::j:
	case op::jl:
	case op::jr:
	case op::lbi:
		return std::make_pair(0, 0);
		break;
	}
}