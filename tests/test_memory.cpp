#include "gtest/gtest.h"

#include "program_memory.h"

#include <stdexcept>

const unsigned int expected_mem_size = 1024;

TEST(memory, memory_size)
{
	Memory mem;
	EXPECT_EQ(expected_mem_size, mem.size());
}

TEST(memory, memory_stores)
{
	Memory mem;
	for(int i = 0; i < expected_mem_size; ++i) {
		mem.set(i, i % 256);
	}

	for(int i = 0; i < expected_mem_size; ++i) {
		ASSERT_EQ(i % 256, mem.get(i));
	}
}

TEST(memory, memory_invalid_location)
{
	Memory mem;

	EXPECT_THROW(mem.set(expected_mem_size + 1, 0), std::out_of_range);
	EXPECT_THROW(mem.get(expected_mem_size + 1), std::out_of_range);

	// Valid range is < expected_mem_size, and does not include it
	EXPECT_THROW(mem.set(expected_mem_size, 0), std::out_of_range);
	EXPECT_THROW(mem.get(expected_mem_size), std::out_of_range);

	// Must write a whole word at at time, so this shouldn't work either
	EXPECT_THROW(mem.set(expected_mem_size - 1, 0), std::out_of_range);
	EXPECT_THROW(mem.get(expected_mem_size - 1), std::out_of_range);

	// But these should work
	EXPECT_NO_THROW(mem.set(expected_mem_size - 2, 0));
	EXPECT_NO_THROW(mem.get(expected_mem_size - 2));
}
