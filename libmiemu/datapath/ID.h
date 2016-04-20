#ifndef ID_H
#define ID_H

#include "register_file.h"
#include "signals.h"

class ID
{
	RegisterFile _register_file;

	Controls _controls;
	IFID _ifid;

	IDEX _signals_out;
	uint16_t _new_pc_address_out;

public:
	void signals_in(const IFID&, const Controls&, uint8_t write_reg, uint16_t write_data, bool stall);
	void tick();
	void tock();
	IDEX signals_out() const;
	uint16_t new_pc_address_out() const;

private:
	void recompute_signals_out();
	void recompute_new_pc_address_out();
};

#endif
