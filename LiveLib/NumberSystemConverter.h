#pragma once
#include "livelib.h"
#include "bit_stream.h"

namespace livelib {
	namespace numsysconverter {

		namespace convert_util {
			uint8_t charToUInt(char ch, uint8_t numberSystem);
			char UIntToChar(uint8_t number, uint8_t numberSystem);
		}

		struct ConvertConfig {
		private:
			static const double e;
		public:
			uint8_t fromNumberSystem;
			uint8_t toNumberSystem;
			uint8_t countOfBitsFromNS;
			uint8_t countOfBitsToNS;

			ConvertConfig(uint8_t fromNumberSystem, uint8_t toNumberSystem);
		};
		
		
		BitStream* convertTo(std::string number, ConvertConfig config);
		BitStream* convertTo(uintmax number, ConvertConfig config);

		std::string toString(BitStream* bs, ConvertConfig config);
	}
}