#include "convert_util.h"
namespace livelib {
	namespace convert_util {
		uint8_t convert_util::charToUInt(char ch, uint8_t numberSystem) {
			uint8_t result;
			if (ch >= '0' && ch <= '9') {
				result = ch - '0';
			} else if (ch >= 'A' && ch <= 'Z') {
				result = ch - 'A' + 10;
			} else if (ch >= 'a' && ch <= 'z') {
				result = ch - 'a' + 10;
			}

			if (result >= numberSystem) {
				throw "Wrong character";
			} else {
				return result;
			}
		}

		char UIntToChar(uint8_t number, uint8_t numberSystem) {
			if (number >= numberSystem) {
				throw "Wrong number";
			} else {
				if (number < 10) {
					return '0' + number;
				} else {
					return 'A' + (number - 10);
				}
			}
		}
	}
}