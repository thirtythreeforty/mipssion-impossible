#include "controller.h"

void Controller::signals_in(uint16_t instruction)
{
	_instruction = instruction;
	_opcode = _instruction & 0xF000;
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
	case ADDI:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case ADD:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case SUB:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case AND:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::And;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case OR:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Or;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case XOR:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Xor;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case SLL:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::ShiftLeft;
		ex_controls.alu_src = 1;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case SRL:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 1;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::ShiftRight;
		ex_controls.alu_src = 1;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case BLT:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 1;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case J:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		//ex_controls.alu_op = 1001;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case JL:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		//ex_controls.alu_op = 1010;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case JR:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 1;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		//ex_controls.alu_op = 1011;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case BEQ:
		//IF
		if_controls.use_new_address = 1;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 1;
		id_controls.jump = 0;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		ex_controls.alu_op = ALUOp::Subtract;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case LW:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 0;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 1;
		break;

	case SW:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = DONT_CARE;
		id_controls.reg_write = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 0;

		//MEM
		mem_controls.mem_write = 1;

		//WB
		wb_controls.mem_to_reg = 0;
		break;

	case LBI:
		//IF
		if_controls.use_new_address = 0;

		//ID
		id_controls.branch_lt = 0;
		id_controls.branch_z = 0;
		id_controls.jump = 0;
		id_controls.reg_dst = 0;
		id_controls.reg_write = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;

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
