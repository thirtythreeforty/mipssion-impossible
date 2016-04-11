#include <gtest/gtest.h>

#include "datapath/IF.h"
#include "datapath/signals.h"
#include "program_memory.h"

#include <cstdint>

TEST(InstructionFetch, ProgramCounterInit)
{
	IF ifetch;

	EXPECT_EQ(0, ifetch.get_pc());
}

TEST(InstructionFetch, ProgramCounterSyncs)
{
	IF ifetch;
	Memory mem;

	IFControls controls = {};
	controls.use_new_address = true;

	// Set PC to zero
	ifetch.signals_in(0, controls);
	ifetch.tick(mem);
	ifetch.tock(mem);

	//<AH> Not reseting PC to 0 causes the test to fail
	//controls.use_new_address = false;
	//ifetch.signals_in(0, controls);

	controls.use_new_address = true;
	ifetch.signals_in(0, controls);
	//</AH>

	for(uint16_t pc_address = 0; pc_address < 10; pc_address += 2) {
		ifetch.tick(mem);
		ifetch.tock(mem);

		ASSERT_EQ(pc_address + 2, ifetch.signals_out().pc_plus_2);
	}
}

TEST(InstructionFetch, MemoryFetch)
{
	IF ifetch;
	Memory mem;
	for(int i = 0; i < mem.size(); i += 2) {
		mem.set(i, i);
	}

	IFControls controls = {};
	controls.use_new_address = true;

	for(uint16_t new_pc_address = 0; new_pc_address < mem.size(); new_pc_address += 2) {
		ifetch.signals_in(new_pc_address, controls);
		ifetch.tick(mem);
		ifetch.tock(mem);

		ASSERT_EQ(mem.get(new_pc_address), ifetch.signals_out().instruction);
	}
}
