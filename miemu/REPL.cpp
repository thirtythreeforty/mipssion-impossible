#include "REPL.h"

#include "instructions.h"

#include "termcolor/termcolor.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>

void REPL::print_status()
{
	if(show_IFID) print_IFID();
	if(show_IDEX) print_IDEX();
	if(show_EXMEM) print_EXMEM();
	if(show_MEMWB) print_MEMWB();
	if(show_Registers) print_Registers();
	if(show_Memory) print_Memory();
}

void REPL::run_to_halt()
{
	while(!is_halted()) {
		step();
	}
}

bool REPL::is_at(uint16_t i)
{
	return emu.get_datapath().get_IF().signals_out().instruction == i;
}

void REPL::step()
{
	emu.step();
}

void REPL::print_prompt()
{
	auto status = (is_halted() ? "Halted" : "Ready");

	std::cout
		<< termcolor::green << termcolor::bold << status
		<< termcolor::reset
		<< termcolor::green << " (PC = " << std::setw(4) << std::setfill('0') << std::hex << emu.get_datapath().get_IFID().pc_plus_2 << ") > "
		<< termcolor::reset;
	std::cout << std::setfill(' ');
}

enum class Modifier {
	hex8,
	hex16,
	dec,
	boolean,
};

using Item = std::tuple<const char*, Modifier, uint16_t>;
void print_contents(const char* header, std::vector<Item> items)
{
	std::cout << termcolor::blue << termcolor::bold << header << "\n";
	for(auto len = std::strlen(header); len > 0; --len) {
		std::cout << "-";
	}
	std::cout << "\n" << termcolor::reset;

	if(items.empty())
		return;

	auto largest_name = std::max_element(items.cbegin(), items.cend(), [](Item a, Item b) {
		return strlen(std::get<0>(a)) < strlen(std::get<0>(b));
	});

	auto width = strlen(std::get<0>(*largest_name));

	for(const auto& item: items) {
		std::cout << std::setw(width) << std::get<0>(item) << " : ";

		switch(std::get<1>(item)) {
		case Modifier::hex8:
			std::cout << std::hex << std::setw(2) << std::setfill('0') << std::get<2>(item);
			break;
		case Modifier::hex16:
			std::cout << std::hex << std::setw(4) << std::setfill('0') << std::get<2>(item);
			break;
		case Modifier::dec:
			std::cout << std::dec << std::get<2>(item);
			break;
		case Modifier::boolean:
			std::cout << (std::get<2>(item) ? "true" : "false");
			break;
		}

		std::cout << std::setfill(' ');
		std::cout << "\n";
	}

	std::cout << "\n";
}

unsigned int ceil_div(unsigned int x, unsigned int y)
{
	return (x + y - 1) / y;
}

template<typename F>
void print_mem(uint16_t max_address, uint8_t width, uint8_t skip, F f)
{
	// Header
	std::cout << std::setw(4) << "" << " ";
	for(int c = 0; c < width; c += skip) {
		std::cout << termcolor::cyan << std::setw(4) << std::hex << c << " ";
	}
	std::cout << termcolor::reset << "\n";

	for(int r = 0; r < ceil_div(max_address, width * skip); ++r) {
		std::cout << termcolor::cyan << "  " << std::setw(2) << std::hex << std::setfill('0') << r * width << termcolor::reset << " ";
		for(int c = 0; c < width; c += skip) {
			std::cout << std::setw(4) << std::hex << std::setfill('0') << f(r * width + c) << " ";
		}
		std::cout << termcolor::reset << "\n";
	}
	std::cout << std::setfill(' ') << "\n";
}

void REPL::print_IFID() {
	const auto& signals = emu.get_datapath().get_IFID();

	print_contents("IFID", {
		std::make_tuple("Instruction", Modifier::hex16, signals.instruction),
		std::make_tuple("PC + 2", Modifier::hex16, signals.pc_plus_2)
	});
}

void REPL::print_IDEX() {
	const auto& signals = emu.get_datapath().get_IDEX();

	print_contents("IDEX", {
		std::make_tuple("Register 1 data", Modifier::hex16, signals.data1),
		std::make_tuple("Register 2 data", Modifier::hex16, signals.data2),
		std::make_tuple("Write register", Modifier::hex8, signals.write_reg),
		std::make_tuple("Literal data", Modifier::hex16, signals.write_data),
	});
}

void REPL::print_EXMEM() {
	const auto& signals = emu.get_datapath().get_EXMEM();

	print_contents("EXMEM", {
		std::make_tuple("ALU output", Modifier::hex16, signals.alu_output),
		std::make_tuple("Write register", Modifier::hex8, signals.write_reg),
		std::make_tuple("Literal data", Modifier::hex16, signals.write_data),
	});
}

void REPL::print_MEMWB() {
	const auto& signals = emu.get_datapath().get_MEMWB();

	print_contents("MEMWB", {
		std::make_tuple("ALU output", Modifier::hex16, signals.alu_output),
		std::make_tuple("Memory contents", Modifier::hex16, signals.memory_data),
		std::make_tuple("Write register", Modifier::hex8, signals.write_reg),
	});
}

void REPL::print_Registers() {
	print_contents("Registers", {});
	print_mem(16, 4, 1, [this](int i){ return emu.get_datapath().get_ID().get_register_file().get_register(i); });
}

void REPL::print_Memory() {
	print_contents("Memory", {});
	print_mem(max_mem_address, 16, 2, [this](int i){ return emu.get_memory().get(i); });
}

