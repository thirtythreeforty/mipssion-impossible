#include "signals.h"

class HDU {

public:
	void signals_in(const IFID&, const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	bool signals_out() const;

private:
	IFID _ifid;
	IDEX _idex;
	EXMEM _exmem;
	MEMWB _memwb;
};