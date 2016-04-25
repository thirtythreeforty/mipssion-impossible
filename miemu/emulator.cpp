#include <iostream>
#include <fstream>

#include "termcolor/termcolor.hpp"

#include "libmiemu.h"

#include "REPL.h"
#include "load.h"
#include "trim_string.h"

int do_load(Emulator& emu, int argc, const char* argv[])
{
	if(argc < 2) {
		return -1;
	}

	// Open the files
	std::fstream mem_file(argv[1], std::ios::in);
	if(!mem_file.good()) {
		std::cerr << "Cannot open memory image \"" << argv[1] << "\"!\n";
		return -1;
	}

	std::fstream reg_file(argv[2], std::ios::in);
	if(!reg_file.good()) {
		std::cerr << "Cannot open register image \"" << argv[1] << "\"!\n";
		return -1;
	}

	load_stream(emu.get_datapath().get_ID().get_register_file(), reg_file);
	return load_stream(emu.get_memory(), mem_file);
}

std::string read_command(REPL& repl, const std::string& prev_cmd)
{
	bool good;
	std::string cmd;
	do {
		repl.print_prompt();
		good = false;

		std::getline(std::cin, cmd);

		if(cmd == "") {
			// Special case to handle Ctrl-D
			if(!std::cin.good()) {
				cmd = "finish";
				std::cout << "\n";
			}
			else {
				cmd = prev_cmd;
			}
		}

		trim(cmd);

		good = (
			cmd == "finish" ||
			cmd == "step" ||
			cmd == "go" ||
			cmd.find("show ") == 0 ||
			cmd.find("unshow ") == 0 ||
			cmd == "help"
		);

		if(!good) {
			std::cout
				<< termcolor::red << "Bad command; type `help` for a list"
				<< termcolor::reset << "\n";
		}
	} while(!good && std::cin.good());

	return cmd;
}

void do_repl(Emulator& emu, unsigned int max_addr)
{
	REPL repl(emu);

	repl.max_mem_address = max_addr;

	std::string cmd;
	do {
		repl.print_status();
		cmd = read_command(repl, cmd);

		auto words = split(cmd, ' ');
		if(cmd == "finish") {
			break;
		}
		else if(cmd == "go") {
			repl.run_to_halt();
		}
		else if(cmd == "step") {
			repl.step();
		}
		else if(words[0] == "show" || words[0] == "unshow") {
			bool* setting;
			bool value = (words[0] == "show");

			for(auto it = words.begin() + 1; it != words.end(); ++it) {
				std::transform(it->begin(), it->end(), it->begin(), ::toupper);
				if(*it == "IFID") {
					setting = &repl.show_IFID;
				}
				else if(*it == "IDEX") {
					setting = &repl.show_IDEX;
				}
				else if(*it == "EXMEM") {
					setting = &repl.show_EXMEM;
				}
				else if(*it == "MEMWB") {
					setting = &repl.show_MEMWB;
				}
				else if(*it == "REGISTERS") {
					setting = &repl.show_Registers;
				}
				else if(*it == "MEMORY") {
					setting = &repl.show_Memory;
				}
				else {
					std::cout << termcolor::red << "Bad descriptor `" << *it << "`" << termcolor::reset << std::endl;
					continue;
				}

				*setting = value;
			}
		}
		else if(words[0] == "help") {
			std::cout <<
				"Try one of the following commands:\n"
				"  - step           Step to the next instruction\n"
				"  - go             Run until HALT instruction is loaded\n"
				"  - finish         Immediately stop execution and print state\n"
				"  - show (args)    Show data, where (args) is one or more of:\n"
				"                    - IFID\n"
				"                    - IDEX\n"
				"                    - EXMEM\n"
				"                    - MEMWB\n"
				"                    - registers\n"
				"                    - memory\n"
				"  - unshow (args)  Stop showing shown data\n";
		}
	} while(std::cin.good());

	repl.show_IFID = true;
	repl.show_IDEX = true;
	repl.show_EXMEM = true;
	repl.show_MEMWB = true;
	repl.show_Registers = true;
	repl.show_Memory = true;

	repl.print_status();
}

void print_help()
{
	std::cerr << "Please provide a memory image and a register initialization file." << std::endl;
}

int main(int argc, const char* argv[])
{
	Emulator emu;

	int max_addr = do_load(emu, argc, argv);
	if(max_addr >= 0) {
		do_repl(emu, max_addr);
	}
	else {
		print_help();
	}
}
