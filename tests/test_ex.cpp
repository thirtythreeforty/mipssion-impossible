#include <gtest/gtest.h>

#include "datapath/EX.h"
#include "instructions.h"
#include "controller.h"
#include <iostream>

//Use read2 from IDEX if ALUSRC is 0
TEST(EX, ALUSRCData2)
{
	IDEX idex;
	EXMEM exmem;
	EX ex;
	FRWD_Out fwd = {};

	idex.data1 = 2;
	idex.data2 = 4;

	idex.ex_controls.alu_op = ALUOp::Add;
	idex.ex_controls.alu_src = 0;

	ex.signals_in(idex, fwd);
	ex.tick();
	ex.tock();
	exmem = ex.signals_out();
	
	EXPECT_EQ(idex.data2, (exmem.alu_output - idex.data1));
}

//Use constant from IDEX based if ALUSRC is 1
TEST(EX, ALUSRCConst)
{
	IDEX idex;
	EXControls exControls;
	EX ex;
	EXMEM exmem;
	FRWD_Out fwd = {};
	
	idex.data1 = 2;
	idex.write_data = 4;
	idex.ex_controls.alu_op = ALUOp::Add;
	idex.ex_controls.alu_src = 1;

	ex.signals_in(idex, fwd);
	ex.tick();
	ex.tock();
	exmem = ex.signals_out();
	

	EXPECT_EQ(idex.write_data, (exmem.alu_output - idex.data1));
}

//Test ALUOP sends the correct command to the ALU
TEST(EX, ALUOP)
{
	IDEX idex;
	EXControls exControls;
	EX ex;
	EXMEM exmem;
	FRWD_Out fwd = {};

	idex.data1 = 4;
	idex.data2 = 2;

	idex.ex_controls.alu_op = ALUOp::Subtract;
	idex.ex_controls.alu_src = 0;

	ex.signals_in(idex, fwd);
	ex.tick();
	ex.tock();
	exmem = ex.signals_out();

	EXPECT_EQ(2, exmem.alu_output);
}
