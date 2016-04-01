#ifndef LIBMIEMU_H
#define LIBMIEMU_H

#include "datapath.h"
#include "program_memory.h"
#include "controller.h"

class Emulator
{
	Datapath _datapath;
	Memory _memory;
	Controller _controller;

public:
	void step();

	const Datapath& datapath() const { return _datapath; }
	const Memory& memory() const { return _memory; };
	const Controller& controller() const { return _controller; };
};

#endif
