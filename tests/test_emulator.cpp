#include <gtest/gtest.h>
#include <iterator>

#include "libmiemu.h"
#include "instructions.h"

template<typename T>
uint16_t init_mem(Memory& mem, const T& instructions)
{
	static const unsigned int needed_nops = 4;

	unsigned int i = 0;
	for(auto it = instructions.cbegin(); it != instructions.cend(); ++it, i += 2) {
		mem.set(i, *it);
	}
	for(unsigned int n = 0; n < needed_nops; i += 2, ++n) {
		mem.set(i, inst::nop());
	}

	return i;
}

void step_emulator_to(Emulator& emulator, const uint16_t finish)
{
	while(emulator.get_datapath().get_IF().get_pc() != finish) {
		emulator.step();
	}
}

TEST(Emulator, add)
{
	Emulator emulator;

	std::array<uint16_t, 5> instructions = {
		inst::lbi(reg::a0, 2),
		inst::lbi(reg::a1, 2),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::add(reg::a2, reg::a0, reg::a1),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(2 + 2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, addi)
{
	Emulator emulator;

	std::array<uint16_t, 4> instructions = {
		inst::lbi(reg::a0, 2),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::addi(reg::a2, reg::a0, 2),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(2 + 2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, sub)
{
	Emulator emulator;

	std::array<uint16_t, 5> instructions = {
		inst::lbi(reg::a0, 6),
		inst::lbi(reg::a1, 2),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::sub(reg::a2, reg::a0, reg::a1),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6 - 2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, and)
{
	Emulator emulator;

	std::array<uint16_t, 5> instructions = {
		inst::lbi(reg::a0, 6),
		inst::lbi(reg::a1, 2),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::and_(reg::a2, reg::a0, reg::a1),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6 & 2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, or)
{
	Emulator emulator;

	std::array<uint16_t, 5> instructions = {
		inst::lbi(reg::a0, 6),
		inst::lbi(reg::a1, 8),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::or_(reg::a2, reg::a0, reg::a1),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6 | 8, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, xor)
{
	Emulator emulator;

	std::array<uint16_t, 5> instructions = {
		inst::lbi(reg::a0, 6),
		inst::lbi(reg::a1, 8),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::xor_(reg::a2, reg::a0, reg::a1),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6 ^ 8, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a2));
}

TEST(Emulator, sll)
{
	Emulator emulator;

	std::array<uint16_t, 4> instructions = {
		inst::lbi(reg::a0, 6),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::sll(reg::a0, reg::a0, 3),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6 << 3, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
}

TEST(Emulator, srl)
{
	Emulator emulator;

	std::array<uint16_t, 4> instructions = {
		inst::lbi(reg::a0, 25),
		inst::nop(), // hazard avoidance
		inst::nop(),
		inst::srl(reg::a0, reg::a0, 3),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(25 >> 3, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
}

TEST(Emulator, lw)
{
	Emulator emulator;

	std::array<uint16_t, 2> instructions = {
		inst::nop(),
		inst::lw(reg::a1, reg::zero, 2),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	// Should load its own program code
	EXPECT_EQ(inst::lw(reg::a1, reg::zero, 2), emulator.get_datapath().get_ID().get_register_file().get_register(reg::a1));
}

TEST(Emulator, j)
{
	Emulator emulator;

	std::array<uint16_t, 4> instructions = {
		inst::j(2),
		inst::lbi(reg::a0, 2),
		inst::j(8),
		inst::lbi(reg::a1, 4)
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
	EXPECT_EQ(0, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a1));
}

TEST(Emulator, jl)
{
	Emulator emulator;

	std::array<uint16_t, 4> instructions = {
		inst::nop(),
		inst::jl(6),
		inst::lbi(reg::a0, 2),
		inst::nop()
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(4, emulator.get_datapath().get_ID().get_register_file().get_register(14));
	EXPECT_EQ(0, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
}

TEST(Emulator, jr)
{
	Emulator emulator;

	std::array<uint16_t, 8> instructions = {
		inst::nop(),
		inst::jl(8),
		inst::lbi(reg::a0, 2),
		inst::j(14),
		inst::nop(), // Clear data hazard before jr
		inst::nop(),
		inst::jr(),
		inst::nop()
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(4, emulator.get_datapath().get_ID().get_register_file().get_register(14));
	EXPECT_EQ(2, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
}

TEST(Emulator, beq)
{
	Emulator emulator;

	std::array<uint16_t, 6> instructions = {
		inst::lbi(reg::a0, 2),
		inst::nop(), // hazard avoidance
		inst::beq(reg::zero, reg::zero, 2), // this is 2 + next instruction
		inst::lbi(reg::v0, 6), // should not execute
		inst::beq(reg::zero, reg::a0, 2),
		inst::lbi(reg::v1, 8) // should execute
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(0, emulator.get_datapath().get_ID().get_register_file().get_register(reg::v0));
	EXPECT_EQ(8, emulator.get_datapath().get_ID().get_register_file().get_register(reg::v1));
}

TEST(Emulator, blt)
{
	Emulator emulator;

	std::array<uint16_t, 6> instructions = {
		inst::lbi(reg::a0, 2),
		inst::nop(), // hazard avoidance for second blt
		inst::blt(reg::zero, reg::zero, 4), // false
		inst::lbi(reg::v0, 6), // should execute
		inst::blt(reg::zero, reg::a0, 4), // true
		inst::lbi(reg::v1, 8) // should not execute
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6, emulator.get_datapath().get_ID().get_register_file().get_register(reg::v0));
	EXPECT_EQ(0, emulator.get_datapath().get_ID().get_register_file().get_register(reg::v1));
}

TEST(Emulator, sw)
{
	Emulator emulator;

	std::array<uint16_t, 2> instructions = {
		inst::nop(),
		inst::sw(reg::a1, reg::zero, 2),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);

	EXPECT_NE(0, emulator.get_memory().get(2));

	step_emulator_to(emulator, finish);

	// Should overwrite its own program code
	EXPECT_EQ(0, emulator.get_memory().get(2));
}

TEST(Emulator, lbi)
{
	Emulator emulator;

	std::array<uint16_t, 1> instructions = {
		inst::lbi(reg::a0, 6),
	};

	auto finish = init_mem(emulator.get_memory(), instructions);
	step_emulator_to(emulator, finish);

	EXPECT_EQ(6, emulator.get_datapath().get_ID().get_register_file().get_register(reg::a0));
}
