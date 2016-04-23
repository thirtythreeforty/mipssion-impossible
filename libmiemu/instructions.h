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
		link = 14,
	};
}

namespace op
{
	enum {
		addi = 0b0000,
		add = 0b0001,
		sub = 0b0010,
		and = 0b0011,
		or = 0b0100,
		xor = 0b0101,
		sll = 0b0110,
		srl = 0b0111,
		blt = 0b1000,
		j = 0b1001,
		jl = 0b1010,
		jr = 0b1011,
		beq = 0b1100,
		lw = 0b1101,
		sw = 0b1110,
		lbi = 0b1111,
	};
}
namespace inst
{
	namespace
	{
		inline uint16_t rtype(const uint8_t opcode, const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2) {
			return (opcode << 12) | (write_reg << 8) | (reg1 << 4) | (reg2 << 0);
		}

		inline uint16_t jtype(const uint8_t opcode, const uint16_t address) {
			return (opcode << 12) | (address >> 1);
		}

		inline uint16_t itype(const uint8_t opcode, const uint8_t write_reg, const uint8_t read_reg, const uint8_t constant) {
			assert(constant <= 0xF);
			return (opcode << 12) | (write_reg << 8) | (read_reg << 4) | (constant << 0);
		}
	}

inline uint16_t addi(const uint8_t write_reg, const uint8_t read_reg, const uint8_t constant)
{
	return itype(0x0, constant, read_reg, write_reg);
}

inline uint16_t nop()
{
	return addi(0, 0, 0);
}

inline uint16_t add(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x1, write_reg, reg1, reg2);
}

inline uint16_t sub(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x2, write_reg, reg1, reg2);
}

inline uint16_t and_(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x3, write_reg, reg1, reg2);
}

inline uint16_t or_(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x4, write_reg, reg1, reg2);
}

inline uint16_t xor_(const uint8_t write_reg, const uint8_t reg1, const uint8_t reg2)
{
	return rtype(0x5, write_reg, reg1, reg2);
}

inline uint16_t sll(const uint8_t write_reg, const uint8_t reg1, const uint8_t shift)
{
	return itype(0x6, shift, reg1, write_reg);
}

inline uint16_t srl(const uint8_t write_reg, const uint8_t reg1, const uint8_t shift)
{
	return itype(0x7, shift, reg1, write_reg);
}

inline uint16_t j(const uint16_t address)
{
	return jtype(0x9, address);
}

inline uint16_t jl(const uint16_t address)
{
	return jtype(0xA, address);
}

inline uint16_t jr()
{
	return jtype(0xB, 0);
}

inline uint16_t blt(const uint8_t reg1, const uint8_t reg2, const uint8_t offset)
{
	assert(offset <= 0xF);
	uint8_t extend_off = offset >= 0x8 ? offset | 0xF0 : offset;
	return itype(0x8, reg2, reg1, (extend_off >> 1) & 0xF);
}

inline uint16_t beq(const uint8_t reg1, const uint8_t reg2, const uint8_t offset)
{
	assert(offset <= 0xF);
	uint8_t extend_off = offset >= 0x8 ? offset | 0xF0 : offset;
	return itype(0xC, reg2, reg1, (extend_off >> 1) & 0xF);
}

inline uint16_t halt()
{
	return beq(reg::zero, reg::zero, 0xE);
}

inline uint16_t lw(const uint8_t write_reg, const uint8_t addr_reg, const uint8_t constant)
{
	return itype(0xD, constant, addr_reg, write_reg);
}

inline uint16_t sw(const uint8_t read_reg, const uint8_t addr_reg, const uint8_t constant)
{
	return itype(0xE, constant, addr_reg, read_reg);
}

inline uint16_t lbi(const uint8_t reg, const uint8_t constant)
{
	return itype(0xF, (constant >> 4) & 0xF, constant & 0xF, reg);
}

}

#endif
