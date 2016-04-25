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
	uint8_t read1;
	uint8_t read2;
	uint16_t data1;
	uint16_t data2;
	FRWD_Out _fwdout;
	bool _stall;

public:
	void signals_in(const IFID&, const Controls&, uint8_t write_reg, uint16_t write_data, FRWD_Out fwdout, bool stall);
	void tick();
	void tock();
	IDEX signals_out() const;
	uint16_t new_pc_address_out() const;

	const RegisterFile& get_register_file() const { return _register_file; }

private:
	void recompute_signals_out();
	void recompute_new_pc_address_out();
};

#endif
