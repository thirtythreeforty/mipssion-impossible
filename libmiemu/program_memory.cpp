#include "program_memory.h"

std::size_t Memory::size() const
{
	return memSize;
}

void Memory::set(uint16_t location, uint16_t data)
{
	if (location >= memSize)
		throw std::out_of_range("Location greater than memory size");
		
	if ((location % 2) != 0)
		throw std::out_of_range("Must write to aligned location");
		
		

	memArray[location] = data;
	
}

uint16_t Memory::get(uint16_t location) const
{
	if (location >= memSize)
		throw std::out_of_range("Location greater than memory size");
		
	if ((location % 2) != 0)
		throw std::out_of_range("Must read from aligned location");
		

	return memArray[location];
}
