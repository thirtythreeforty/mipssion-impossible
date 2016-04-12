#include "gtest/gtest.h"

#include "program_memory.h"

#include <stdexcept>

const unsigned int expected_mem_size = 1024;

TEST(memory, ProperSize)
{
	Memory mem;
	EXPECT_EQ(expected_mem_size, mem.size());
}

TEST(memory, Store)
{
	Memory mem;
	for(int i = 0; i < expected_mem_size; i += 2) {
		mem.set(i, i % 65536);
	}

	for(int i = 0; i < expected_mem_size; i += 2) {
		ASSERT_EQ(i % 65536, mem.get(i));
	}
}

TEST(memory, InvalidLocation)
{
	Memory mem;

	EXPECT_THROW(mem.set(expected_mem_size + 2, 0), std::out_of_range);
	EXPECT_THROW(mem.get(expected_mem_size + 2), std::out_of_range);

	// Valid range is < expected_mem_size, and does not include it
	EXPECT_THROW(mem.set(expected_mem_size, 0), std::out_of_range);
	EXPECT_THROW(mem.get(expected_mem_size), std::out_of_range);

	// But these should work
	EXPECT_NO_THROW(mem.set(expected_mem_size - 2, 0));
	EXPECT_NO_THROW(mem.get(expected_mem_size - 2));
}

TEST(memory, UnalignedAccess)
{
	Memory mem;

	// Must write at aligned locations, so this shouldn't work
	EXPECT_THROW(mem.set(1, 0), std::out_of_range);
	EXPECT_THROW(mem.get(1), std::out_of_range);
}
