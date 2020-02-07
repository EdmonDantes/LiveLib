#pragma once
#include "livelib.h"
#include "bit_stream.h"

namespace livelib {
	namespace numsysconverter {

		struct NumberSystem {
			uint16 numberSystem;
			uint8 countOfBits;

			NumberSystem();
			NumberSystem(uint16 numberSystem);
		};

		struct ConvertConfig {
			NumberSystem from;
			NumberSystem to;

			ConvertConfig(NumberSystem from, NumberSystem to);
			ConvertConfig(uint16 from, uint16 to);
		};
		
		/*
			Method for convert number from one number system to other
			Convert number with size = *N* from *A* number system to *B* number system
			O(n^2 * log2(A)) +- 1%
			
			Max number system = 2^SystemBits
			x86 = 2^32
			x64 = 2^64
		*/
		BitStream* convertTo(std::string number, ConvertConfig config);
		BitStream* convertTo(uintmax number, ConvertConfig config);

		std::string toString(BitStream* bs, NumberSystem to);
	}
}