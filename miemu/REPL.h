#ifndef EXAMINE_H
#define EXAMINE_H

#include "libmiemu.h"
#include "instructions.h"

class REPL
{
	Emulator& emu;

public:
	explicit REPL(Emulator& emu)
		: emu(emu)
	{}

	enum class DisplayType {
		IFID,
		IDEX,
		EXMEM,
		MEMWB,
		Registers,
		Memory,
	};

	void print_status();
	void print_prompt();

	void step();
	void flush() { for(int i = 0; i < 5; ++i) step(); }
	void run_to_halt();
	void run_to_address(uint16_t);

	bool is_halted() { return is_at(inst::halt()); }

	bool show_IFID, show_IDEX, show_EXMEM, show_MEMWB, show_Registers, show_Memory;
	uint16_t max_mem_address;

private:
	bool is_at(uint16_t);

	void print_IFID();
	void print_IDEX();
	void print_EXMEM();
	void print_MEMWB();
	void print_Registers();
	void print_Memory();
};

#endif
