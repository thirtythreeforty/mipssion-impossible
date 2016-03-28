#ifndef ID_H
#define ID_H

#include "register_file.h"
#include "signals.h"

class ID
{
	RegisterFile _register_file;

	void signals_in(const IFID&, uint8_t write_reg, uint16_t write_data);
	void tick();
	void tock();
	IDEX signals_out() const;
};

#endif
