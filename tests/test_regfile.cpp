#include "gtest/gtest.h"

#include "datapath/register_file.h"

#include <stdexcept>

const unsigned int expected_registers = 16;

TEST(regfile, ReadWrite) {
	RegisterFile regfile;

	for(int i = 0; i < expected_registers; ++i) {
		regfile.signals_in(0, 0, true, i, i);
		regfile.tick();
		regfile.tock();
	}

	for(int i = 0; i < expected_registers; ++i) {
		regfile.signals_in(i, i, false, 0, 0);
		regfile.tick();
		regfile.tock();
		ASSERT_EQ(i, regfile.data1_out());
		ASSERT_EQ(i, regfile.data2_out());
	}
}

TEST(regfile, WriteEnable) {
	RegisterFile regfile;

	for(int i = 0; i < expected_registers; ++i) {
		regfile.signals_in(0, 0, true, i, i);
		regfile.tick();
		regfile.tock();

		// The following should overwrite nothing
		regfile.signals_in(0, 0, false, i, 0);
		regfile.tick();
		regfile.tock();
	}

	for(int i = 0; i < expected_registers; ++i) {
		regfile.signals_in(i, i, false, 0, 0);
		regfile.tick();
		regfile.tock();
		ASSERT_EQ(i, regfile.data1_out());
		ASSERT_EQ(i, regfile.data2_out());
	}
}

TEST(regfile, ReadBeforeWrite) {
	RegisterFile regfile;

	// Store 42 in a register
	regfile.signals_in(1, 1, true, 0, 42);
	regfile.tick();
	regfile.tock();

	// Overwrite with 6*9. 42 should still be accessible until after tock
	regfile.signals_in(0, 0, true, 0, 6 * 9);
	regfile.tick();
	EXPECT_EQ(42, regfile.data1_out());
	regfile.tock();
	EXPECT_EQ(6 * 9, regfile.data1_out());
}

TEST(regfile, OutOfBoundsError) {
	RegisterFile regfile;

	EXPECT_THROW(regfile.signals_in(expected_registers, 0, false, 0, 0), std::out_of_range);
	EXPECT_THROW(regfile.signals_in(0, expected_registers, false, 0, 0), std::out_of_range);
	EXPECT_THROW(regfile.signals_in(0, 0, false, expected_registers, 0), std::out_of_range);
	EXPECT_THROW(regfile.signals_in(expected_registers + 1, 0, false, 0, 0), std::out_of_range);
	EXPECT_THROW(regfile.signals_in(0, expected_registers + 1, false, 0, 0), std::out_of_range);
	EXPECT_THROW(regfile.signals_in(0, 0, false, expected_registers + 1, 0), std::out_of_range);

	EXPECT_NO_THROW(regfile.signals_in(expected_registers - 1, 0, false, 0, 0));
	EXPECT_NO_THROW(regfile.signals_in(0, expected_registers - 1, false, 0, 0));
}
