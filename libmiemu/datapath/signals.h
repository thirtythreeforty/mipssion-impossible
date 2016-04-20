#ifndef SIGNALS_H
#define SIGNALS_H

#include <cstdint>

enum class ALUOp {
	Add,
	Subtract,
	ShiftLeft,
	ShiftRight,
	And,
	Or,
	Xor,
};

struct IFControls {
	// If false, use PC + 2
	bool use_new_address = false;
};

struct IDControls {
	bool reg_position = false;
	bool branch_z = false;
	bool branch_lt = false;
	bool jump = false;
	bool reg_write = false;
	bool use_8bit_data = false;
};

struct EXControls {
	bool alu_src = false;

	ALUOp alu_op = ALUOp::Add;
};

struct MEMControls {
	bool mem_write = false;
};

struct WBControls {
	bool mem_to_reg = false;
};

struct Controls {
	IFControls if_controls;
	IDControls id_controls;
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;
};

struct ControlInputs {
	uint16_t instruction = 0;
};

struct IFID {
	uint16_t instruction = 0;
	uint16_t pc_plus_2 = 0;
};

struct IDEX {
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t data1 = 0;
	uint16_t data2 = 0;

	int16_t branch_offset = 0;

	uint8_t write_reg = 0;
	uint16_t write_data = 0;
};

struct EXMEM {
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t alu_output = 0;
	uint16_t write_data = 0;

	uint8_t write_reg = 0;
	
};

struct MEMWB {
	WBControls wb_controls;

	uint16_t memory_data = 0;
	uint16_t alu_output = 0;

	uint8_t write_reg = 0;
};

#endif
