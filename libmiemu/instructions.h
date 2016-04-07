#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <cassert>
#include <cstdint>

namespace reg
{
	enum {
		zero = 0,
		v0,
		v1,
		v2,
		v3,
		t0,
		t1,
		t2,
		t3,
		a0,
		a1,
		a2,
		a3,
	};
}

namespace inst
{
	namespace
	{
		constexpr uint16_t rtype(const uint8_t opcode, const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2) {
			return (opcode << 12) | (write_reg << 8) | (reg1 << 4) | (reg2 << 0);
		}

		constexpr uint16_t jtype(const uint8_t opcode, const uint16_t address) {
			return (opcode << 12) | (address >> 1);
		}

		constexpr uint16_t itype(const uint8_t opcode, const uint8_t write_reg, const uint8_t read_reg, const uint8_t constant) {
			assert(constant <= 0xF);
			return (opcode << 12) | (write_reg << 8) | (read_reg << 4) | (constant << 0);
		}
	}

constexpr uint16_t addi(const uint8_t write_reg, const uint8_t read_reg, const uint8_t constant)
{
	return itype(0x0, write_reg, read_reg, constant);
}

constexpr uint16_t add(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x1, write_reg, reg1, reg2);
}

constexpr uint16_t j(const uint16_t address)
{
	return jtype(0x9, address);
}

constexpr uint16_t blt(const uint8_t reg1, const uint8_t reg2, const uint8_t offset)
{
	assert(offset <= 0xF);
	uint8_t extend_off = offset >= 0x8 ? offset | 0xF0 : offset;
	return itype(0x8, extend_off >> 1, reg2, reg1);
}

constexpr uint16_t beq(const uint8_t reg1, const uint8_t reg2, const uint8_t offset)
{
	assert(offset <= 0xF);
	uint8_t extend_off = offset >= 0x8 ? offset | 0xF0 : offset;
	return itype(0xC, extend_off >> 1, reg2, reg1);
}

constexpr uint16_t lw(const uint8_t write_reg, const uint8_t addr_reg, const uint8_t constant)
{
	return itype(0xD, constant, addr_reg, write_reg);
}

constexpr uint16_t sw(const uint8_t read_reg, const uint8_t addr_reg, const uint8_t constant)
{
	return itype(0xE, constant, addr_reg, read_reg);
}

constexpr uint16_t lbi(const uint8_t reg, const uint8_t constant)
{
	return itype(0xF, (constant << 4) & 0xF, constant & 0xF, reg);
}

}

#endif
