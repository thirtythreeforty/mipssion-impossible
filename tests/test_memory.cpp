#include "gtest/gtest.h"

#include "memory.h"

TEST(memory, memory_sane)
{
	Memory mem;
	ASSERT_EQ(512, mem.size());
}
