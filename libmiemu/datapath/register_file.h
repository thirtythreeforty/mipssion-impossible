#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <array>
#include <cstdint>
#include <tuple>

class RegisterFile
{
	std::array<uint16_t, 16> _registers;
	uint8_t _read1, _read2;
	bool _write;
	uint8_t _write_reg;
	uint16_t _write_data;

	uint16_t _data1_out, _data2_out;

public:
	RegisterFile();
	void signals_in(uint8_t read1,
	                uint8_t read2,
	                bool write,
	                uint8_t write_reg,
	                uint16_t write_data);
	void tick();
	void tock();

	uint16_t data1_out() const;
	uint16_t data2_out() const;

	uint16_t get_register(uint8_t reg) const;
	void set_register(uint8_t reg, uint16_t data);
};

#endif
