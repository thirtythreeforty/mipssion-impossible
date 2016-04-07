#include <gtest/gtest.h>

#include "instructions.h"

TEST(Instructions, addi)
{
	EXPECT_EQ(0x0F21, inst::addi(1, 2, 15));
}

TEST(Instructions, add)
{
	EXPECT_EQ(0x1123, inst::add(1, 2, 3));
}

TEST(Instructions, j)
{
	EXPECT_EQ(0x9001, inst::j(0x2));
}

TEST(Instructions, blt)
{
	EXPECT_EQ(0x8121, inst::blt(1, 2, 0x2));
}

TEST(Instructions, beq)
{
	EXPECT_EQ(0xC121, inst::beq(1, 2, 0x2));
}

TEST(Instructions, lw)
{
	EXPECT_EQ(0xD021, inst::lw(1, 2, 0));
}

TEST(Instructions, sw)
{
	EXPECT_EQ(0xE021, inst::sw(1, 2, 0));
}

TEST(Instructions, lbi)
{
	EXPECT_EQ(0xFFF1, inst::lbi(1, 0xFF));
}
