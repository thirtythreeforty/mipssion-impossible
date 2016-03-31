#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <cstdint>

class Memory
{
public:
	std::size_t size() const;

	void set(uint16_t location, uint16_t data);
	uint16_t get(uint16_t location) const;
};

#endif
