#include <gtest/gtest.h>

#include "instructions.h"

TEST(Instructions, addi)
{
	EXPECT_EQ(0x0F21, inst::addi(reg::v0, reg::v1, 15));
}

TEST(Instructions, add)
{
	EXPECT_EQ(0x1123, inst::add(reg::v0, reg::v1, 3));
}

TEST(Instructions, sub)
{
	EXPECT_EQ(0x2123, inst::sub(reg::v0, reg::v1, reg::v2));
}

TEST(Instructions, and)
{
	EXPECT_EQ(0x3123, inst::and_(reg::v0, reg::v1, reg::v2));
}

TEST(Instructions, or)
{
	EXPECT_EQ(0x4123, inst::or_(reg::v0, reg::v1, reg::v2));
}

TEST(Instructions, xor)
{
	EXPECT_EQ(0x5123, inst::xor_(reg::v0, reg::v1, reg::v2));
}

TEST(Instructions, sll)
{
	EXPECT_EQ(0x6F21, inst::sll(reg::v0, reg::v1, 15));
}

TEST(Instructions, srl)
{
	EXPECT_EQ(0x7F21, inst::srl(reg::v0, reg::v1, 15));
}

TEST(Instructions, j)
{
	EXPECT_EQ(0x9001, inst::j(0x2));
}

TEST(Instructions, blt)
{
	EXPECT_EQ(0x8211, inst::blt(reg::v0, reg::v1, 0x2));
}

TEST(Instructions, beq)
{
	EXPECT_EQ(0xC211, inst::beq(reg::v0, reg::v1, 0x2));
}

TEST(Instructions, lw)
{
	EXPECT_EQ(0xD021, inst::lw(reg::v0, reg::v1, 0));
}

TEST(Instructions, sw)
{
	EXPECT_EQ(0xE021, inst::sw(reg::v0, reg::v1, 0));
}

TEST(Instructions, lbi)
{
	EXPECT_EQ(0xFFF1, inst::lbi(reg::v0, 0xFF));
}
