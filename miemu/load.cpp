#include "load.h"

#include <algorithm>
#include <functional>
#include <string>

void unparsable_message(const std::string& line)
{
	std::cerr << "Warning, skipping unparsable line " << line << "\n";
}

template<typename Callable>
int do_load(Callable c, std::istream& stream, unsigned int step, unsigned int max, unsigned int offset)
{
	std::string str;
	unsigned int loc;
	for(loc = offset; stream.good() && loc < max; loc += step) {
		std::getline(stream, str);

		if(str.length() == 0) continue;

		uint16_t i;
		try {
			i = std::stoul(str, 0, 16);
		}
		catch(std::invalid_argument& e) {
			unparsable_message(str);
			continue;
		}
		catch(std::overflow_error& e) {
			unparsable_message(str);
			continue;
		}

		c(loc, i);
	}

	return loc;
}

int load_stream(Memory& mem, std::istream& stream, unsigned int offset)
{
	using namespace std::placeholders;
	return do_load(std::bind(&Memory::set, &mem, _1, _2), stream, 2, mem.size(), offset);
}

int load_stream(RegisterFile& reg, std::istream& stream, unsigned int offset)
{
	using namespace std::placeholders;
	return do_load(std::bind(&RegisterFile::set_register, &reg, _1, _2), stream, 1, 16, offset);
}
