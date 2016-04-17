#include <gtest/gtest.h>

#include "datapath/MEM.h"
#include "instructions.h"
#include "controller.h"
#include "datapath/register_file.h"
#include "program_memory.h"


//Load word from memory into register
TEST(MEM, lw)
{
	//MemRead always 1
	Memory mem;
	EXMEM exmem;
	MEMWB memwb;
	MEM memoryblock;
	MEMControls memcontrols;

	//Hardcode register value to read back
	mem.set(0x0002, 0x1234);

	exmem.mem_controls.mem_write = 0;
	exmem.alu_output = 0x0002;
	

	memoryblock.signals_in(exmem);
	memoryblock.tick(mem);
	memoryblock.tock(mem);


	ASSERT_EQ(0x1234, memoryblock.signals_out().memory_data);
	
}

TEST(MEM, move_to_buffer)
{
	Memory mem;
	EXMEM exmem;
	MEMWB memwb;
	MEM memoryblock;

	exmem.alu_output = 0x0002;

	memoryblock.signals_in(exmem);
	memoryblock.tick(mem);
	memoryblock.tock(mem);

	EXPECT_EQ(exmem.alu_output, memoryblock.signals_out().alu_output);
}

//Load word from register into memory
//Writes WriteData to the address specified
TEST(MEM, sw)
{
	//ReadData always 1
	Memory mem;
	EXMEM exmem;
	MEMWB memwb;
	MEM memoryblock;

	exmem.mem_controls.mem_write = 1;
	exmem.alu_output = 0x0002;
	exmem.write_data = 0x1234;


	memoryblock.signals_in(exmem);
	memoryblock.tick(mem);
	memoryblock.tock(mem);

	EXPECT_EQ(0x1234, mem.get(0x0002));

}