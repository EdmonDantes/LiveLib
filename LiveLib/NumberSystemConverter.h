#pragma once
#include "livelib.h"
#include "bit_stream.h"

namespace livelib {
	namespace numsysconverter {

		struct ConvertConfig {
		public:
			static const double e;
			uint8_t fromNumberSystem;
			uint8_t toNumberSystem;
			uint8_t countOfBitsFromNS;
			uint8_t countOfBitsToNS;

			ConvertConfig(uint8_t fromNumberSystem, uint8_t toNumberSystem);
		};
		
		/*
			Method for convert number from one number system to other
			Convert number with size = n from a number system to b number system
			k - computer coefficient
			O(log(a) / log(b) * n * k) +- 3%
			
			Max number system 254
			Recomend max number system 127
		*/
		BitStream* convertTo(std::string number, ConvertConfig config);
		BitStream* convertTo(uintmax number, ConvertConfig config);

		std::string toString(BitStream* bs, ConvertConfig config);
	}
}