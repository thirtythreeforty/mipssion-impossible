#include "controller.h"

#define ADDI 0b0000
#define ADD 0b0001
#define SUB 0b0010
#define AND 0b0011
#define OR 0b0100
#define XOR 0b0101
#define SLL 0b0110
#define SRL 0b0111
#define BLT 0b1000
#define J 0b1001
#define JL 0b1010
#define JR 0b1011
#define BEQ 0b1100
#define LW 0b1101
#define SW 0b1110
#define LBI 0b1111

#define DONT_CARE 0

void Controller::signals_in(ControlInputs inputs)
{
	_opcode = (inputs.instruction & 0xF000) >> 12;
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
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 1;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = DONT_CARE;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 0;
		id_controls.use_8bit_data = 0;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;

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
		id_controls.reg_position = 0;
		id_controls.reg_write = 1;
		id_controls.use_8bit_data = 1;

		//EX
		ex_controls.alu_op = ALUOp::Add;
		ex_controls.alu_src = 1;

		//MEM
		mem_controls.mem_write = 0;

		//WB
		wb_controls.mem_to_reg = 0;
		break;
	}

	all_controls.id_controls = id_controls;
	all_controls.if_controls = if_controls;
	all_controls.ex_controls = ex_controls;
	all_controls.mem_controls = mem_controls;
	all_controls.wb_controls = wb_controls;

	return all_controls;
}
