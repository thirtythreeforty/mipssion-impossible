#include "program_memory.h"

std::size_t Memory::size() const
{
	return memSize;
}

void Memory::set_datapath(uint16_t location, uint16_t data)
{
	uint16_t elem = location >> 1;
	if(elem > size()) {
		return;
	}
	memArray[location >> 1] = data;
}

uint16_t Memory::get_datapath(uint16_t location) const
{
	uint16_t elem = location >> 1;
	if(elem > size()) {
		return 0;
	}
	return memArray[location >> 1];
}

void Memory::set(uint16_t location, uint16_t data)
{
	if (location >= memSize)
		throw std::out_of_range("Location greater than memory size");
		
	if ((location % 2) != 0)
		throw std::out_of_range("Must write to aligned location");

	set_datapath(location, data);
}

uint16_t Memory::get(uint16_t location) const
{
	if (location >= memSize)
		throw std::out_of_range("Location greater than memory size");
		
	if ((location % 2) != 0)
		throw std::out_of_range("Must read from aligned location");

	return get_datapath(location);
}
