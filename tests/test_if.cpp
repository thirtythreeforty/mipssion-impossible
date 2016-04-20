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
	ifetch.signals_in(0, controls, 0);
	ifetch.tick(mem);
	ifetch.tock(mem);

	controls.use_new_address = false;
	ifetch.signals_in(0, controls, 0);

	for(uint16_t pc_address = 0; pc_address < 10; pc_address += 2) {
		ASSERT_EQ(pc_address + 2, ifetch.signals_out().pc_plus_2);

		ifetch.tick(mem);
		ifetch.tock(mem);
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
		ifetch.signals_in(new_pc_address, controls, 0);
		ifetch.tick(mem);
		ifetch.tock(mem);

		ASSERT_EQ(mem.get(new_pc_address), ifetch.signals_out().instruction);
	}
}
