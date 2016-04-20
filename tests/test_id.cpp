#include "gtest/gtest.h"

#include "datapath/ID.h"
#include "instructions.h"
#include "controller.h"

#include <array>

#define DONTCARE 0

TEST(ID, JumpPCAddress)
{
	IFID ifid;
	ifid.pc_plus_2 = 0xEEEE;
	ifid.instruction = inst::j(0x0010);

	Controller controller;
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	ID id;
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();

	// New address should be 0xE000 | 0x0010
	EXPECT_EQ(0xE000 | 0x0010, id.new_pc_address_out());
}

TEST(ID, RegistersWrite)
{
	ID id;
	IFID ifid;
	Controller controller;

	for(int i = 1; i < 16; ++i) {
		ifid.instruction = inst::add(0, i, i);
		controller.signals_in(ifid.instruction);
		Controls ctrl = controller.controls_out();

		id.signals_in(ifid, ctrl, i, i, 0);
		id.tick();
		id.tock();
	}

	for(int i = 1; i < 16; ++i) {
		ifid.instruction = inst::add(0, i, i);
		controller.signals_in(ifid.instruction);
		Controls ctrl = controller.controls_out();

		ctrl.id_controls.reg_write = false;

		id.signals_in(ifid, ctrl, 0, 0, 0);
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

	Controller controller;

	ifid.instruction = DONTCARE;
	ifid.pc_plus_2 = 0xC0DE;
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	id.signals_in(ifid, ctrl, 1, 1, 0);
	id.tick();
	id.tock();
	id.signals_in(ifid, ctrl, 2, 2, 0);
	id.tick();
	id.tock();

	// This should not "branch"
	ifid.instruction = inst::blt(2, 1, 4);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2, id.new_pc_address_out());

	// This SHOULD "branch"
	ifid.instruction = inst::blt(1, 2, 4);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 + 4, id.new_pc_address_out());

	// This should not "branch"
	ifid.instruction = inst::beq(2, 1, 4);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2, id.new_pc_address_out());

	// This SHOULD "branch"
	ifid.instruction = inst::beq(0, 0, 4);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 + 4, id.new_pc_address_out());

	// This branches backward by 2
	ifid.instruction = inst::beq(0, 0, 0xE);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();
	id.signals_in(ifid, ctrl, 0, 0, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(ifid.pc_plus_2 - 2, id.new_pc_address_out());
}

TEST(ID, WriteRegDecode)
{
	ID id;

	IFID ifid;
	ifid.instruction = inst::add(reg::v0, DONTCARE, DONTCARE);

	Controller controller;
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	ctrl.id_controls.reg_write = true;
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(reg::v0, id.signals_out().write_reg);

	ctrl.id_controls.reg_write = false;
	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(reg::zero, id.signals_out().write_reg);
}

TEST(ID, WriteDataSignExtend)
{
	ID id;
	IFID ifid;
	Controller controller;

	const std::array<uint16_t (*)(const uint8_t, const uint8_t, const uint8_t), 3> itypes = {
		inst::addi,
		inst::lw,
		inst::sw,
		// Test lbi separately
	};

	for(const auto& itype: itypes) {
		for(int i = 0; i < 0x8; ++i) {
			ifid.instruction = itype(DONTCARE, DONTCARE, i);
			controller.signals_in(ifid.instruction);
			Controls ctrl = controller.controls_out();

			id.signals_in(ifid, ctrl, 0, 0, 0);
			id.tick();
			id.tock();
			ASSERT_EQ(i, id.signals_out().write_data);
		}

		// Must sign-extend if constant is 0x8 thru 0xF
		for(int i = 0x8; i < 0xF; ++i) {
			ifid.instruction = inst::addi(DONTCARE, DONTCARE, i);
			controller.signals_in(ifid.instruction);
			Controls ctrl = controller.controls_out();

			id.signals_in(ifid, ctrl, 0, 0, 0);
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
	Controller controller;

	// Should sign-extend negative
	ifid.instruction = inst::lbi(DONTCARE, 0xFF);
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(0xFFFF, id.signals_out().write_data);

	// Should sign-extend positive
	ifid.instruction = inst::lbi(DONTCARE, 0x7F);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();

	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(0x007F, id.signals_out().write_data);
}

TEST(ID, LBIRegisterValues)
{
	ID id;
	IFID ifid;
	Controller controller;

	// When handling the LBI instruction, The ID stage should emit 0x0000 for
	// data1 and data2 so the EX stage can add zero to the immediate operand
	// (of course, this needs the proper commands from the controller).
	ifid.instruction = inst::lbi(DONTCARE, 0xFF);
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	// If this isn't handled correctly, the ID stage will read the 0xF register.
	// So write data there so we can detect that
	id.signals_in(ifid, ctrl, 0xF, 0xC0DE, 0);
	id.tick();
	id.tock();
	EXPECT_EQ(0, id.signals_out().data1);
	EXPECT_EQ(0, id.signals_out().data2);
}

TEST(ID, OutputsChangeOnTick)
{
	ID id;
	IFID ifid;
	Controller controller;

	ifid.instruction = inst::lbi(reg::a1, 0xFF);
	controller.signals_in(ifid.instruction);
	Controls ctrl = controller.controls_out();

	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);
	id.tick();
	id.tock();

	// Outputs should now be in a fully defined state, so copy them
	IDEX before_idex = id.signals_out();

	ifid.instruction = inst::beq(reg::v0, reg::v1, 4);
	controller.signals_in(ifid.instruction);
	ctrl = controller.controls_out();

	id.signals_in(ifid, ctrl, DONTCARE, DONTCARE, 0);

	// Outputs should not change until tick() / tock()
	EXPECT_EQ(before_idex.data1, id.signals_out().data1);
	EXPECT_EQ(before_idex.data2, id.signals_out().data2);
	EXPECT_EQ(before_idex.branch_offset, id.signals_out().branch_offset);
	EXPECT_EQ(before_idex.write_reg, id.signals_out().write_reg);
	EXPECT_EQ(before_idex.write_data, id.signals_out().write_data);

	id.tick();
	id.tock();

	// The registers are all zero, so this won't be true.
	// EXPECT_NE(before_idex.data1, id.signals_out().data1);
	// EXPECT_NE(before_idex.data2, id.signals_out().data2);

	// branch_offset is not used at all and should be removed, ultimately
	// EXPECT_NE(before_idex.branch_offset, id.signals_out().branch_offset);

	EXPECT_NE(before_idex.write_reg, id.signals_out().write_reg);
	EXPECT_NE(before_idex.write_data, id.signals_out().write_data);
}
