#include "hazard_detection.h"
#include "signals.h"


void HDU::signals_in(const IFID& ifid, const IDEX& idex, const EXMEM& exmem, const MEMWB& memwb) {

}

void HDU::tick() {

}

void HDU::tock() {

}

bool HDU::signals_out() const {

	//needs to return 1 to stall, 0 for normal op
	return 0;
}

