#include "load.h"

#include <algorithm>
#include <string>

void unparsable_message(const std::string& line)
{
	std::cerr << "Warning, skipping unparsable line " << line << "\n";
}

int load_stream(Memory& mem, std::istream& stream, unsigned int offset)
{
	std::string str;
	unsigned int loc;
	for(loc = offset; stream.good(); loc += 2) {
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

		mem.set(loc, i);
	}

	return loc;
}
