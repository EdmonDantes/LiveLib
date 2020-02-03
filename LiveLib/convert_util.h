#pragma once
#include "livelib.h"

namespace livelib {
	namespace convert_util {
		uint8_t charToUInt(char ch, uint8_t numberSystem);
		char UIntToChar(uint8_t number, uint8_t numberSystem);
	}
}