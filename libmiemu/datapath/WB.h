#ifndef WB_H
#define WB_H

#include "signals.h"

#include <cstdint>

class WB
{
	uint8_t write_reg;
	uint16_t write_data;

public:
	void signals_in(const MEMWB&);
	uint8_t write_reg_out() const;
	uint16_t write_data_out() const;
};

#endif
