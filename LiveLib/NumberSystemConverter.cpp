#include <sstream>
#include <cmath>
#include "NumberSystemConverter.h"
#include "array_util.h"

namespace livelib {
	namespace numsysconverter {
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

		const double ConvertConfig::e = 0.000001;

		ConvertConfig::ConvertConfig(uint8_t fromNumberSystem, uint8_t toNumberSystem) {
			this->fromNumberSystem = fromNumberSystem;
			this->toNumberSystem = toNumberSystem;

			double tmp = log2(fromNumberSystem);
			this->countOfBitsFromNS = ((uint8_t) tmp);
			this->countOfBitsFromNS += (tmp - this->countOfBitsToNS > e ? 1 : 0);

			tmp = log2(toNumberSystem);
			this->countOfBitsToNS = ((uint8_t) tmp);
			this->countOfBitsToNS += (tmp - this->countOfBitsToNS > e ? 1 : 0);
			
		}

		BitStream* convertTo(std::string number, ConvertConfig config) {
			uint8_t* originalNumber = new uint8_t[number.length()];
			BitStream* resultNumber = new BitStream(
				std::log(config.fromNumberSystem) / std::log(config.toNumberSystem) * number.length() * config.countOfBitsToNS
			);

			for (int i = 0; i < number.length(); i++) {
				originalNumber[i] = convert_util::charToUInt(number[i], config.fromNumberSystem);
			}

			int startIndexOriginal = 0;
			int endIndexOriginal = number.length();

			while (startIndexOriginal < endIndexOriginal) {
				unsigned short tmp = 0;
				int i = startIndexOriginal;
				for (; i < endIndexOriginal || tmp != 0 && i < number.length(); i++) {
					tmp = tmp * config.fromNumberSystem + originalNumber[i];
					originalNumber[i] = tmp / config.toNumberSystem;
					tmp %= config.toNumberSystem;

					if (i == startIndexOriginal && originalNumber[i] == 0) {
						startIndexOriginal++;
					}

					if (i >= endIndexOriginal) {
						endIndexOriginal = i + 1;
					}
				}

				while (originalNumber[endIndexOriginal - 1] == 0 && endIndexOriginal > startIndexOriginal) {
					endIndexOriginal--;
				}

				resultNumber->append(tmp, config.countOfBitsToNS);
			}

			delete[] originalNumber;
			
			return resultNumber;
		}

		BitStream* convertTo(uintmax number, ConvertConfig config) {
			BitStream* result = new BitStream(sizeof(number) * 8);
			result->append(number, true);
			return result;
		}

		std::string toString(BitStream * bs, ConvertConfig config) {
			std::stringstream ss;
			uintmax size = bs->getCountOfBits() / config.countOfBitsToNS;
			for (int i = size - 1; i > -1; i--) {
				ss << convert_util::UIntToChar(bs->get(i, config.countOfBitsToNS), config.toNumberSystem);
			}
			return ss.str();
		}
	}
}
