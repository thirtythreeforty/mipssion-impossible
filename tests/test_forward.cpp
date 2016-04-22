#include <gtest/gtest.h>
#include "datapath\forwarding.h"
#include "datapath\signals.h"

TEST(Forward, detect_EXMEM_hazard_ALUSRC1)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;
	
	//ID/EX
	idex.read1 = 0x0002;
	idex.read2 = 0x0004;
	
	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x1234;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();
	
	EXPECT_EQ(1, fwd_out.ALUSRC1);
	EXPECT_EQ(exmem.alu_output, fwd_out.exmem_alu_output);
	EXPECT_EQ(0, fwd_out.ALUSRC2);
}

TEST(Forward, detect_EXMEM_hazard_ALUSRC2)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0004;
	idex.read2 = 0x0002;

	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x1234;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(0, fwd_out.ALUSRC1);
	EXPECT_EQ(1, fwd_out.ALUSRC2);
	EXPECT_EQ(exmem.alu_output, fwd_out.exmem_alu_output);
}

TEST(Forward, detect_MEMWB_hazard_ALUSRC1)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0002;
	idex.read2 = 0x0004;

	//EX/ME
	exmem.write_reg = 0x1234;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0002;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(2, fwd_out.ALUSRC1);
	//EXPECT_EQ(memwb.alu_output, fwd_out.memwb_data);
	EXPECT_EQ(0, fwd_out.ALUSRC2);
}

TEST(Forward, detect_MEMWB_hazard_ALUSRC2)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0004;
	idex.read2 = 0x0002;

	//EX/ME
	exmem.write_reg = 0x1234;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0002;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(0, fwd_out.ALUSRC1);
	EXPECT_EQ(2, fwd_out.ALUSRC2);
	EXPECT_EQ(memwb.memory_data, fwd_out.memwb_data);
}

TEST(Forward, detect_double_hazard_EXMEM)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0002;
	idex.read2 = 0x0002;

	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0004;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(1, fwd_out.ALUSRC1);
	EXPECT_EQ(1, fwd_out.ALUSRC2);
	EXPECT_EQ(exmem.alu_output, fwd_out.exmem_alu_output);
}

TEST(Forward, detect_double_hazard_MEMWB)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0004;
	idex.read2 = 0x0004;

	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0004;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(2, fwd_out.ALUSRC1);
	EXPECT_EQ(2, fwd_out.ALUSRC2);
	EXPECT_EQ(memwb.memory_data, fwd_out.memwb_data);
}

TEST(Forward, detect_double_hazard_EXMEM_MEMWB)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0002;
	idex.read2 = 0x0004;

	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0004;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(1, fwd_out.ALUSRC1);
	EXPECT_EQ(exmem.alu_output, fwd_out.exmem_alu_output);
	EXPECT_EQ(2, fwd_out.ALUSRC2);
	EXPECT_EQ(memwb.memory_data, fwd_out.memwb_data);

}

TEST(Forward, detect_double_hazard_MEMWB_EXMEM)
{
	Forward fwd;
	FRWD_Out fwd_out;
	IDEX idex;
	EXMEM exmem;
	MEMWB memwb;

	//ID/EX
	idex.read1 = 0x0004;
	idex.read2 = 0x0002;

	//EX/ME
	exmem.write_reg = 0x0002;

	//MEM/WB
	memwb.wb_controls.mem_to_reg = 0;
	memwb.write_reg = 0x0004;

	fwd.signals_in(idex, exmem, memwb);
	fwd.tick();
	fwd.tock();
	fwd_out = fwd.signals_out();

	EXPECT_EQ(2, fwd_out.ALUSRC1);
	EXPECT_EQ(memwb.memory_data, fwd_out.memwb_data);
	EXPECT_EQ(1, fwd_out.ALUSRC2);
	EXPECT_EQ(exmem.alu_output, fwd_out.exmem_alu_output);
}

TEST(Forward, detect_no_hazard)
{
	Forward fwd;
	FRWD_Out fwd_out;

	//EXPECT_EQ(exmem.alu_output, memoryblock.signals_out().alu_output);
}