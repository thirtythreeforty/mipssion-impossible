#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <cstdint>
#include <array>
class Memory
{
private: 
	static const std::size_t memSize = 1024;
	std::array<uint16_t, memSize> memArray;

public:
	std::size_t size() const;

	void set(uint16_t location, uint16_t data);
	uint16_t get(uint16_t location) const;
};

#endif
