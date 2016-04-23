#include "controller.h"
#include "instructions.h"


#define DONT_CARE 0

void Controller::signals_in(uint16_t instruction)
{
	_opcode = (instruction & 0xF000) >> 12;
}

Controls Controller::controls_out() const
{
	Controls all_controls;
	IFControls if_controls;
	IDControls id_controls;
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;

	switch (_opcode) {
	case op::addi:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;
		

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::add:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::sub:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::and:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::And;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::or:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Or;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::xor:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Xor;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::sll:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::ShiftLeft;
		ex_controls.alu_src = 1;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::srl:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::ShiftRight;
		ex_controls.alu_src = 1;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::blt:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 1;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::j:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		//ex_controls.alu_op = 1001;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::jl:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		//ex_controls.alu_op = 1010;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::jr:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		//ex_controls.alu_op = 1011;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::beq:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 1;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::lw:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 1;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 1;
		break;

	case op::sw:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 1;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case op::lbi:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;
		mem_controls.mem_read = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 1;
		break;
	}

	all_controls.id_controls = id_controls;
	all_controls.if_controls = if_controls;
	all_controls.ex_controls = ex_controls;
	all_controls.mem_controls = mem_controls;
	all_controls.wb_controls = wb_controls;

	return all_controls;
}
