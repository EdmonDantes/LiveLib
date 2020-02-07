#include <sstream>
#include <cmath>
#include "NumberSystemConverter.h"
#include "array_util.h"
#include "convert_util.h"

namespace livelib {
	namespace numsysconverter {

		NumberSystem::NumberSystem() {}

		NumberSystem::NumberSystem(uint16 numberSystem) {
			this->numberSystem = numberSystem;
			double tmp = log2(numberSystem);
			this->countOfBits = (uint16) tmp;
			this->countOfBits += (tmp - this->countOfBits > _LPL_MAX_PRECISION ? 1 : 0);
		}

		ConvertConfig::ConvertConfig(NumberSystem from, NumberSystem to) {
			this->from = from;
			this->to = to;
		}

		ConvertConfig::ConvertConfig(uint16 from, uint16 to) {
			this->from = NumberSystem(from);
			this->to = NumberSystem(to);
		}

		BitStream* convertTo(std::string number, ConvertConfig config) {
			uintmax numberLength = number.length();

			BitStream originalNumber = BitStream(numberLength * config.from.countOfBits);
			BitStream* resultNumber = new BitStream(numberLength * config.from.countOfBits);

			const char* numberChars = number.c_str();
			for (int i = 0; i < numberLength; i++) {
				originalNumber.append(convert_util::charToUInt(numberChars[i], config.from.numberSystem), config.from.countOfBits);
			}

			int startIndexOriginal = 0;
			int endIndexOriginal = numberLength;

			while (startIndexOriginal < endIndexOriginal) {
				unsigned short tmp = 0;
				uintmax i = startIndexOriginal;
				for (; i < endIndexOriginal || tmp != 0 && i < numberLength; i++) {
					tmp = tmp * config.from.numberSystem + originalNumber.get(i, config.from.countOfBits);
					originalNumber.set(tmp / config.to.numberSystem, 0, config.from.countOfBits, i, config.from.countOfBits);
					tmp %= config.to.numberSystem;

					if (i == startIndexOriginal && originalNumber.get(i, config.from.countOfBits) == 0) {
						startIndexOriginal++;
					}

					if (i >= endIndexOriginal) {
						endIndexOriginal = i + 1;
					}
				}

				while (originalNumber.get(endIndexOriginal - 1, config.from.countOfBits) == 0 && endIndexOriginal > startIndexOriginal) {
					endIndexOriginal--;
				}

				resultNumber->append(tmp, config.to.countOfBits);
			}
			
			return resultNumber;
		}

		BitStream* convertTo(uintmax number, ConvertConfig config) {
			BitStream* result = new BitStream(sizeof(number) * 8);
			result->append(number, true);
			return result;
		}

		std::string toString(BitStream * bs, NumberSystem to) {
			std::stringstream ss;
			uintmax size = bs->getCountOfBits() / to.countOfBits;
			for (int i = size - 1; i > -1; i--) {
				ss << convert_util::UIntToChar(bs->get(i, to.countOfBits), to.numberSystem);
			}
			return ss.str();
		}
	}
}
