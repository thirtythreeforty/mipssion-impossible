#include "hazard_detection.h"
#include "instructions.h"

void HDU::signals_in(const IFID& ifid, const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb) {

	_ifid = ifid;
	_idex = idex;
	_exmem = exmem;
	_memwb = memwb;

	opcode = (ifid.instruction & 0xF000) >> 12;
	readRegs = getRead(ifid.instruction, opcode);
	
}

void HDU::tick() {
	/*lw check
	if mem read is 1 we have lw instuction
	*/
	
	//check if we need to wait on a lw instruction futher down the pipeline
	if (_idex.mem_controls.mem_read == 1
		&& (_idex.write_reg == readRegs.first
		|| _idex.write_reg == readRegs.second))
	{
		stall = true;
	}
	
	if (opcode == op::lw)
	{

	}
	//branch check
	/*
	
	*/
	else if (opcode == op::beq || opcode == op::blt)
	{

	}
	//for jump instructions check the write reg to see if it is the designated reg for link .. reg::link
	//jl check
	else if (opcode == op::jl)
	{

	}
	//jr check
	else if (opcode == op::jr)
	{

	}
}

void HDU::tock() {

}

bool HDU::signals_out() const {

	//needs to return 1 to stall, 0 for normal op
	return 0;
}

std::pair<uint16_t, uint16_t> getRead(uint16_t _instruction, uint8_t _op)
{
	switch (_op) {
	//reg position 1
	case op::add:
	case op::sub:
	case op::and:
	case op:: or :
	case op::xor:
	case op::sll:
	case op::srl:
		return std::make_pair((_instruction >> 4) & 0x000F, (_instruction >> 0) & 0x000F);
		break;
	// reg position 0
	case op::blt:
	case op::beq:
	case op::lw:
	case op::sw:
		return std::make_pair((_instruction >> 4) & 0x000F, (_instruction >> 8) & 0x000F);
		break;
	//reg position DONT_CARE
	case op::lbi:
	case op::j:
	case op::jl:
	case op::jr:
		return std::make_pair(0, 0);
		break;
}
