#include <sstream>
#include <cmath>
#include "NumberSystemConverter.h"
#include "array_util.h"
#include "convert_util.h"

namespace livelib {
	namespace numsysconverter {

		const double ConvertConfig::e = 0.000001;

		ConvertConfig::ConvertConfig(uint8_t fromNumberSystem, uint8_t toNumberSystem) {
			this->fromNumberSystem = fromNumberSystem;
			this->toNumberSystem = toNumberSystem;

			double tmp = log2(fromNumberSystem);
			this->countOfBitsFromNS = ((uint8_t) tmp);
			this->countOfBitsFromNS += (tmp - this->countOfBitsFromNS > e ? 1 : 0);

			tmp = log2(toNumberSystem);
			this->countOfBitsToNS = ((uint8_t) tmp);
			this->countOfBitsToNS += (tmp - this->countOfBitsToNS > e ? 1 : 0);
			
		}

		BitStream* convertTo(std::string number, ConvertConfig config) {
			BitStream originalNumber = BitStream(number.length() * config.countOfBitsFromNS);
			double tmpSize = std::log(config.fromNumberSystem) / std::log(config.toNumberSystem) * number.length() * config.countOfBitsToNS;
			BitStream* resultNumber = new BitStream(
				(((uintmax) tmpSize) - tmpSize > ConvertConfig::e ? 1 : 0) + tmpSize
			);

			for (int i = 0; i < number.length(); i++) {
				originalNumber.append(convert_util::charToUInt(number[i], config.fromNumberSystem), config.countOfBitsFromNS);
			}

			originalNumber.get(0, config.countOfBitsFromNS);

			int startIndexOriginal = 0;
			int endIndexOriginal = number.length();

			while (startIndexOriginal < endIndexOriginal) {
				unsigned short tmp = 0;
				int i = startIndexOriginal;
				for (; i < endIndexOriginal || tmp != 0 && i < number.length(); i++) {
					tmp = tmp * config.fromNumberSystem + originalNumber.get(i, config.countOfBitsFromNS);
					originalNumber.set(tmp / config.toNumberSystem, 0, config.countOfBitsFromNS, i, config.countOfBitsFromNS);
					tmp %= config.toNumberSystem;

					if (i == startIndexOriginal && originalNumber.get(i, config.countOfBitsFromNS) == 0) {
						startIndexOriginal++;
					}

					if (i >= endIndexOriginal) {
						endIndexOriginal = i + 1;
					}
				}

				while (originalNumber.get(endIndexOriginal - 1, config.countOfBitsFromNS) == 0 && endIndexOriginal > startIndexOriginal) {
					endIndexOriginal--;
				}

				resultNumber->append(tmp, config.countOfBitsToNS);
			}
			
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
