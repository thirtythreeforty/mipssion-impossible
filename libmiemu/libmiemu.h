#ifndef LIBMIEMU_H
#define LIBMIEMU_H

#include "datapath.h"
#include "program_memory.h"
#include "controller.h"
#include "datapath/forwarding.h"
#include "hazard_detection.h"

class Emulator
{
	Datapath _datapath;
	Memory _memory;
	Controller _controller;
	Forward _fwd;
	FRWD_Out _fwdout;
	HDU	_hazard;

public:
	void step();

	const Datapath& get_datapath() const { return _datapath; }
	Datapath& get_datapath() { return _datapath; }
	Memory& get_memory() { return _memory; };
	const Controller& get_controller() const { return _controller; };
};

#endif
