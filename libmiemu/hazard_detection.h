#include "datapath/signals.h"
#include <utility>

class HDU {

public:
	void signals_in(const IFID&, const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	bool signals_out() const;
	std::pair<uint16_t, uint16_t> getRead(uint16_t, uint8_t);

private:
	uint8_t opcode;
	std::pair<uint16_t, uint16_t> readRegs;
	bool stall;

	IFID _ifid;
	IDEX _idex;
	EXMEM _exmem;
	MEMWB _memwb;
};