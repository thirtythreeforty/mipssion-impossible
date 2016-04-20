#ifndef FORWARD_H
#define FORWARD_H

#include "signals.h"

class Forward
{
private:

public:
	void signals_in(const IDEX&, const EXMEM&, const MEMWB&);
	void tick();
	void tock();
	FRWD_Out signals_out() const;
};
#endif // !FORWARD_H
