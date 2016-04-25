#include "register_file.h"

RegisterFile::RegisterFile()
	: _registers{0}
{}

void RegisterFile::signals_in(uint8_t read1,
                              uint8_t read2,
                              bool write,
                              uint8_t write_reg,
                              uint16_t write_data)
{
	if(read1 >= _registers.size()) {
		throw std::out_of_range("read1 out of bounds");
	}
	if(read2 >= _registers.size()) {
		throw std::out_of_range("read2 out of bounds");
	}
	if(write_reg >= _registers.size()) {
		throw std::out_of_range("write_reg out of bounds");
	}

	_read1 = read1;
	_read2 = read2;
	_write = write;
	_write_reg = write_reg;
	_write_data = write_data;

	_data1_out = _registers[_read1];
	_data2_out = _registers[_read2];
}

void RegisterFile::tick()
{
	if(_write && _write_reg != 0) {
		_registers[_write_reg] = _write_data;
	}
	_data1_out = _registers[_read1];
	_data2_out = _registers[_read2];
}

void RegisterFile::tock()
{
}

uint16_t RegisterFile::data1_out() const
{
	return _data1_out;
}

uint16_t RegisterFile::data2_out() const
{
	return _data2_out;
}

uint16_t RegisterFile::get_register(uint8_t reg) const
{
	return _registers[reg];
}

void RegisterFile::set_register(uint8_t reg, uint16_t data)
{
	_registers[reg] = data;
}

