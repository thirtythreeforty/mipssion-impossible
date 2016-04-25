#ifndef LOAD_H
#define LOAD_H

#include "program_memory.h"
#include "datapath/register_file.h"

#include <iostream>

int load_stream(Memory&, std::istream&, unsigned int offset = 0);
int load_stream(RegisterFile&, std::istream&, unsigned int offset = 0);

#endif
