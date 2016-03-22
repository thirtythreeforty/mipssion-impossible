#ifndef LIBMIEMU_H
#define LIBMIEMU_H

#include "datapath.h"
#include "memory.h"
#include "controller.h"

class Emulator
{
	Datapath _datapath;
	Memory _memory;
	Controller _controller;

public:
	Emulator();
	~Emulator();

	void run();
	void step();
	const Datapath& datapath() const;
};

#endif
