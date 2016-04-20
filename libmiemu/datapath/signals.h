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
	bool use_new_address;
};

struct IDControls {
	bool reg_position;
	bool branch_z;
	bool branch_lt;
	bool jump;
	bool reg_write;
	bool use_8bit_data;
};

struct EXControls {
	bool alu_src;

	ALUOp alu_op;
};

struct MEMControls {
	bool mem_write;
};

struct WBControls {
	bool mem_to_reg;
};

struct Controls {
	IFControls if_controls;
	IDControls id_controls;
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;
};

struct ControlInputs {
	uint16_t instruction;
};

struct FRWD_Out {
	/*
	0 = use data value
	1 = EXMEM.alu_output
	2 = MEMWB.memory_data  or MEMWB.alu_output //Use wb_controls.mem_to_reg to see which one to pick
												mem_to_reg = 0, alu_output
												mem_to_reg = 1, memory_data
	
	*/
	uint8_t ALUSRC1;
	/* 
	0 = use data vaue  
	1 = EXMEM.alu_output
	2 = MEMWB.memory_data or MEMWB.alu_output //Use wb_controls.mem_to_reg to see which one to pick
												mem_to_reg = 0, alu_output
												mem_to_reg = 1, memory_data
	*/
	uint8_t ALUSRC2;
	//set from exmem buffer
	uint16_t exmem_alu_output;

	//set from memwb based on conditions listed above
	uint16_t memwb_data;
};

struct IFID {
	uint16_t instruction;
	uint16_t pc_plus_2;
};

struct IDEX {
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t data1;
	uint16_t data2;

	uint16_t read1;
	uint16_t read2;

	int16_t branch_offset;

	uint8_t write_reg;
	uint16_t write_data;
};

struct EXMEM {
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t alu_output;
	uint16_t write_data;

	uint8_t write_reg;
	
};

struct MEMWB {
	WBControls wb_controls;

	uint16_t memory_data;
	uint16_t alu_output;

	uint8_t write_reg;
};

#endif
