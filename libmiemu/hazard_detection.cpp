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
#pragma region lw
	//check to see if we need to wait for lw: memRead = 1
	if (_exmem.mem_controls.mem_read == 1
		&& (_idex.write_reg == readRegs.first
			|| _idex.write_reg == readRegs.second))
		stall = true;



#pragma endregion
#pragma region branch
	//check for dependency in ex stage for branch
	if (opcode == op::beq || opcode == op::blt
		&& (_idex.write_reg == readRegs.first
			|| _idex.write_reg == readRegs.second))
		stall = true;
	//check for dependency in mem stage for branch
	if (opcode == op::beq || opcode == op::blt
		&& (_exmem.write_reg == readRegs.first
			|| _exmem.write_reg == readRegs.second))
		stall = true;


#pragma endregion
#pragma region jump
	//if cur inst == jr, check for jl in pipeline'
	/*if(opcode == op::jr
		&& _idex.)*/
#pragma endregion
}

void HDU::tock() {

}

bool HDU::signals_out() const {

	//needs to return 1 to stall, 0 for normal op
	return 0;
}

std::pair<uint8_t, uint8_t> HDU::getRead(uint16_t _instruction, uint8_t _op)
{
	switch (_op)
	{
		//Use reg position 1, to get read reg 2
		case op::add:
		case op::sub:
		case op::and:
		case op:: or :
		case op::xor:
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