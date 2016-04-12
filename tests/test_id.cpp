#include "gtest/gtest.h"

#include "datapath/ID.h"
#include "instructions.h"

#include <array>

#define DONTCARE 0

TEST(ID, JumpPCAddress)
{
	IFID ifid;
	ifid.pc_plus_2 = 0xEEEE;
	ifid.instruction = inst::j(0x0010);

	Controls ctrl;
	ctrl.id_controls.jump = true;

	ID id;
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();

	// New address should be 0xE000 | 0x0010
	EXPECT_EQ(0xE000 | 0x0010, id.new_pc_address_out());
}

TEST(ID, RegistersWrite)
{
	ID id;
	IFID ifid;
	Controls ctrl;

	for(int i = 1; i < 16; ++i) {
		id.signals_in(ifid, ctrl, i, i);
		id.tick();
		id.tock();
	}

	for(int i = 1; i < 16; ++i) {
		ifid.instruction = inst::add(0, i, i);
		id.signals_in(ifid, ctrl, 0, 0);
		id.tick();
		id.tock();
		ASSERT_EQ(i, id.signals_out().data1);
		ASSERT_EQ(i, id.signals_out().data2);
	}
}

TEST(ID, BranchPCAddress)
{
	ID id;
	IFID ifid;
	ifid.pc_plus_2 = 0xC0DE;

	Controls ctrl;

	id.signals_in(ifid, ctrl, 1, 1);
	id.tick();
	id.tock();
	id.signals_in(ifid, ctrl, 2, 2);
	id.tick();
	id.tock();

	// This should not "branch"
	ifid.instruction = inst::blt(2, 1, 4);
	ctrl.id_controls.branch_z = false;
	ctrl.id_controls.branch_lt = true;
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2, id.new_pc_address_out());

	// This SHOULD "branch"
	ifid.instruction = inst::blt(1, 2, 4);
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 + 4, id.new_pc_address_out());

	// This should not "branch"
	ifid.instruction = inst::beq(2, 1, 4);
	ctrl.id_controls.branch_z = true;
	ctrl.id_controls.branch_lt = false;
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2, id.new_pc_address_out());

	// This SHOULD "branch"
	ifid.instruction = inst::beq(0, 0, 4);
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 + 4, id.new_pc_address_out());

	// This branches backward by 2
	ifid.instruction = inst::beq(0, 0, 0xE);
	id.signals_in(ifid, ctrl, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 - 2, id.new_pc_address_out());
}

TEST(ID, WriteRegDecode)
{
	ID id;
	IFID ifid;
	Controls ctrl;

	ifid.instruction = inst::add(reg::v0, DONTCARE, DONTCARE);
	ctrl.id_controls.reg_write = true;
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE);
	id.tick();
	id.tock();
	EXPECT_EQ(reg::v0, id.signals_out().write_reg);

	ctrl.id_controls.reg_write = false;
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE);
	id.tick();
	id.tock();
	EXPECT_EQ(reg::zero, id.signals_out().write_reg);
}

TEST(ID, WriteDataSignExtend)
{
	ID id;
	IFID ifid;
	Controls ctrl;

	const std::array<uint16_t (*)(const uint8_t, const uint8_t, const uint8_t), 3> itypes = {
		inst::addi,
		inst::lw,
		inst::sw,
		// Test lbi separately
	};

	for(const auto& itype: itypes) {
		for(int i = 0; i < 0x8; ++i) {
			ifid.instruction = itype(DONTCARE, DONTCARE, i);
			id.signals_in(ifid, ctrl, 0, 0);
			id.tick();
			id.tock();
			ASSERT_EQ(i, id.signals_out().write_data);
		}

		// Must sign-extend if constant is 0x8 thru 0xF
		for(int i = 0x8; i < 0xF; ++i) {
			ifid.instruction = inst::addi(DONTCARE, DONTCARE, i);
			id.signals_in(ifid, ctrl, 0, 0);
			id.tick();
			id.tock();
			ASSERT_EQ(i | 0xFFF0, id.signals_out().write_data);
		}
	}
}

TEST(ID, WriteDataLBI)
{
	ID id;
	IFID ifid;
	Controls ctrl;

	ctrl.id_controls.use_8bit_data = true;

	// Should sign-extend negative
	ifid.instruction = inst::lbi(DONTCARE, 0xFF);
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE);
	id.tick();
	id.tock();
	EXPECT_EQ(0xFFFF, id.signals_out().write_data);

	// Should sign-extend positive
	ifid.instruction = inst::lbi(DONTCARE, 0x7F);
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE);
	id.tick();
	id.tock();
	EXPECT_EQ(0x007F, id.signals_out().write_data);
}
