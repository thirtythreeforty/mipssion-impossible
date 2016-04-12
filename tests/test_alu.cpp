#include "gtest/gtest.h"

#include "datapath/alu.h"
#include "datapath/signals.h"

TEST(alu, Add) {
	ALU alu;

	alu.signals_in(ALUOp::Add, 2, 2);
	alu.tick();
	alu.tock();
	EXPECT_EQ(2 + 2, alu.data_out());
}

TEST(alu, Sub) {
	ALU alu;

	alu.signals_in(ALUOp::Subtract, 4, 2);
	alu.tick();
	alu.tock();
	EXPECT_EQ(4 - 2, alu.data_out());
}

TEST(alu, Flags) {
	ALU alu;

	// We have some extra cases to check here, because branches use
	// the Z and C flags
	alu.signals_in(ALUOp::Subtract, 2, 4);
	alu.tick();
	alu.tock();
	EXPECT_EQ(uint16_t(2 - 4), alu.data_out());
	EXPECT_EQ(0, alu.z_out());
	EXPECT_EQ(1, alu.c_out());

	alu.signals_in(ALUOp::Subtract, 2, 2);
	alu.tick();
	alu.tock();
	EXPECT_EQ(uint16_t(2 - 2), alu.data_out());
	EXPECT_EQ(1, alu.z_out());
	EXPECT_EQ(0, alu.c_out());
}

TEST(alu, ShiftLeft) {
	ALU alu;

	alu.signals_in(ALUOp::ShiftLeft, 4, 2);
	alu.tick();
	alu.tock();
	EXPECT_EQ(4 << 2, alu.data_out());
}

TEST(alu, ShiftRight) {
	ALU alu;

	alu.signals_in(ALUOp::ShiftRight, 8, 2);
	alu.tick();
	alu.tock();
	EXPECT_EQ(8 >> 2, alu.data_out());
}

TEST(alu, BitwiseAnd) {
	ALU alu;

	alu.signals_in(ALUOp::And, 37, 42);
	alu.tick();
	alu.tock();
	EXPECT_EQ(37 & 42, alu.data_out());
}

TEST(alu, BitwiseOr) {
	ALU alu;

	alu.signals_in(ALUOp::Or, 37, 42);
	alu.tick();
	alu.tock();
	EXPECT_EQ(37 | 42, alu.data_out());
}

TEST(alu, BitwiseXor) {
	ALU alu;

	alu.signals_in(ALUOp::Xor, 37, 42);
	alu.tick();
	alu.tock();
	EXPECT_EQ(37 ^ 42, alu.data_out());
}
