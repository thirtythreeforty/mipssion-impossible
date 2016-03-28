#include "gtest/gtest.h"

#include "program_memory.h"

TEST(memory, memory_sane)
{
	Memory mem;
	ASSERT_EQ(512, mem.size());
}
