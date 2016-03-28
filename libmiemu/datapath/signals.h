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

struct EXControls {
	bool alu_src;
	bool branch_gt;
	bool branch_z;
	bool jump;

	ALUOp alu_op;
};

struct MEMControls {
	bool mem_write;
};

struct WBControls {
	bool mem_to_reg;
	bool reg_write;
};

struct Controls {
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;
};

struct IFID {
	uint16_t instruction;
};

struct IDEX {
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t jump_addr;
	uint16_t pc_plus_2;

	uint16_t data1;
	uint16_t data2;

	int16_t branch_offset;

	uint8_t write_reg;
	uint16_t write_data;
};

struct EXMEM {
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t new_pc_address;
	uint16_t alu_output;
	uint16_t data2;

	uint8_t write_reg;
	uint16_t write_data;
};

struct MEMWB {
	WBControls wb_controls;

	uint16_t new_pc_address;
	uint16_t memory_data;
	uint16_t alu_output;

	uint8_t write_reg;
	uint16_t write_data;
};

#endif
