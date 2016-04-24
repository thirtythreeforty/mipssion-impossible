#include "datapath/signals.h"
#include "instructions.h"
#include <utility>

class HDU {

public:
	void signals_in(const IFID&, const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	bool signals_out() const;
	std::pair<uint8_t, uint8_t> getRead(uint16_t, uint8_t);
	bool run_hazard_unit(const IFID&, const IDEX&, const EXMEM&, const MEMWB&);

private:
	bool stall = 0;
	uint16_t instruction;
	std::pair<uint8_t, uint8_t> readRegs;
	uint8_t opcode;

	IFID _ifid;
	IDEX _idex;
	EXMEM _exmem;
	MEMWB _memwb;
};