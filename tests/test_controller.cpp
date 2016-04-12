#include "gtest/gtest.h"

#include "controller.h"
#include "datapath/signals.h"
#include "instructions.h"

#include <array>

#define DONTCARE 0

TEST(Controller, AssertsWriteReg)
{
	Controller ctrl;

	const std::array<uint16_t, 4> should_set_writereg = {
		inst::addi(1, DONTCARE, DONTCARE),
		inst::add(1, DONTCARE, DONTCARE),
		/*
		inst::sub(1, DONTCARE, DONTCARE),
		inst::and_(1, DONTCARE, DONTCARE),
		inst::or_(1, DONTCARE, DONTCARE),
		inst::xor_(1, DONTCARE, DONTCARE),
		inst::sll(1, DONTCARE, DONTCARE),
		inst::srl(1, DONTCARE, DONTCARE),
		*/
		inst::lw(1, DONTCARE, DONTCARE),
		inst::lbi(1, DONTCARE),
	};

	const std::array<uint16_t, 4> dont_set_writereg = {
		inst::blt(1, DONTCARE, DONTCARE),
		inst::j(0x00DE),
		/*
		inst::jl(0x0ODE),
		inst::jr(),
		*/
		inst::beq(1, DONTCARE, DONTCARE),
		inst::sw(1, DONTCARE, DONTCARE),
	};

	for(const auto inst: should_set_writereg) {
		ctrl.signals_in(inst);
		EXPECT_EQ(1, ctrl.controls_out().id_controls.reg_write) << "Instruction is " << std::hex << inst;
	}

	for(const auto inst: dont_set_writereg) {
		ctrl.signals_in(inst);
		EXPECT_EQ(0, ctrl.controls_out().id_controls.reg_write) << "Instruction is " << std::hex << inst;
	}
}
