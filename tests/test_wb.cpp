#include <gtest/gtest.h>

#include "datapath/WB.h"
#include "instructions.h"
#include "controller.h"

TEST(WB, MemToReg)
{
	WB wb;

	MEMWB memwb;
	memwb.memory_data = 0xDEAD;
	memwb.alu_output = 0xBEEF;
	memwb.write_reg = reg::a1;

	memwb.wb_controls.mem_to_reg = true;
	wb.signals_in(memwb);
	EXPECT_EQ(reg::a1, wb.write_reg_out());
	EXPECT_EQ(memwb.memory_data, wb.write_data_out());

	memwb.wb_controls.mem_to_reg = false;
	wb.signals_in(memwb);
	EXPECT_EQ(reg::a1, wb.write_reg_out());
	EXPECT_EQ(memwb.alu_output, wb.write_data_out());
}
