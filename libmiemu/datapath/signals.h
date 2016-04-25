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

	IFControls() = default;
	IFControls(bool use_new_address)
		: use_new_address(use_new_address)
	{}
};

struct IDControls {
	bool reg_position = false;
	bool branch_z = false;
	bool branch_lt = false;
	bool jump = false;
	bool jump_link = false;
	bool write_link = false;
	bool reg_write = false;
	bool use_8bit_data = false;

	IDControls() = default;
	IDControls(bool reg_position, bool branch_z, bool branch_lt, bool jump, bool jump_link, bool write_link, bool reg_write, bool use_8bit_data)
		: reg_position(reg_position)
		, branch_z(branch_z)
		, branch_lt(branch_lt)
		, jump(jump)
		, jump_link(jump_link)
		, write_link(write_link)
		, reg_write(reg_write)
		, use_8bit_data(use_8bit_data)
	{}
};

struct EXControls {
	bool alu_src = false;
	ALUOp alu_op = ALUOp::Add;

	EXControls() = default;
	EXControls(bool alu_src, ALUOp alu_op)
		: alu_src(alu_src)
		, alu_op(alu_op)
	{}
};

struct MEMControls {
	bool mem_write = false;
	bool mem_read = false;

	MEMControls() = default;
	MEMControls(bool mem_write)
		: mem_write(mem_write)
	{}
};

struct WBControls {
	bool mem_to_reg = false;

	WBControls() = default;
	WBControls(bool mem_to_reg)
		: mem_to_reg(mem_to_reg)
	{}
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

	ControlInputs() = default;
	ControlInputs(uint16_t instruction)
		: instruction(instruction)
	{}
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

	uint8_t REGSRC1;
	uint8_t REGSRC2;
};

struct IFID {
	uint16_t instruction = 0;
	uint16_t pc_plus_2 = 0;

	IFID() = default;
	IFID(uint16_t instruction, uint16_t pc_plus_2)
		: instruction(instruction)
		, pc_plus_2(pc_plus_2)
	{}
};

struct IDEX {
	EXControls ex_controls;
	MEMControls mem_controls;
	WBControls wb_controls;
	uint16_t data1 = 0;
	uint16_t data2 = 0;
	uint8_t read1 = 0;
	uint8_t read2 = 0;
	int16_t branch_offset = 0;

	uint8_t write_reg = 0;
	uint16_t write_data = 0;

	IDEX() = default;
	IDEX(EXControls ex_controls, MEMControls mem_controls, WBControls wb_controls, uint8_t read1, uint8_t read2, uint16_t data1, uint16_t data2, int16_t branch_offset, uint8_t write_reg, uint16_t write_data)
		: ex_controls(ex_controls)
		, mem_controls(mem_controls)
		, wb_controls(wb_controls)
		, read1(read1)
		, read2(read2)
		, data1(data1)
		, data2(data2)
		, branch_offset(branch_offset)
		, write_reg(write_reg)
		, write_data(write_data)
	{}
};

struct EXMEM {
	MEMControls mem_controls;
	WBControls wb_controls;

	uint16_t alu_output = 0;
	uint16_t write_data = 0;

	uint8_t write_reg = 0;

	EXMEM() = default;
	EXMEM(MEMControls mem_controls, WBControls wb_controls, uint16_t alu_output, uint16_t write_data, uint16_t write_reg)
		: mem_controls(mem_controls)
		, wb_controls(wb_controls)
		, alu_output(alu_output)
		, write_data(write_data)
		, write_reg(write_reg)
	{}
};

struct MEMWB {
	WBControls wb_controls;

	uint16_t memory_data = 0;
	uint16_t alu_output = 0;

	uint8_t write_reg = 0;

	MEMWB() = default;
	MEMWB(WBControls wb_controls, uint16_t memory_data, uint16_t alu_output, uint8_t write_reg)
		: wb_controls(wb_controls)
		, memory_data(memory_data)
		, alu_output(alu_output)
		, write_reg(write_reg)
	{}
};

#endif
