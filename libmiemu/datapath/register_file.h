#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <cstdint>
#include <tuple>

class RegisterFile
{
public:
	void signals_in(uint8_t read1,
	                uint8_t read2,
	                uint8_t write_reg,
	                uint16_t write_data);
	void tick();
	void tock();

	uint16_t data1_out() const;
	uint16_t data2_out() const;
};

#endif
