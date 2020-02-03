#include <sstream>
#include <cmath>
#include <iostream>

#include "bit_stream.h"
#include "size_util.h"
#include "array_util.h"
#include "convert_util.h"

namespace livelib {

	using namespace size_util;

	inline uintmax BitStream::catValue(uintmax value, uint8 offset, uint8 length, uint8 endShift) {
		if (length == 0 || offset == innerSize) {
			return 0;
		} else {
			return (((value >> offset) << (innerSize - length)) >> (innerSize - length)) << endShift;
		}
	}

	BitStream::BitStream() {
		value = new uintmax[size = 16];
		memset(value, 0, sizeof(uintmax) * 16);
	}
	BitStream::BitStream(uintmax countOfBits) {
		size = size_util::divSize(countOfBits, innerSize) + (countOfBits % innerSize == 0 ? 0 : 1) + 16;
		value = new uintmax[size];
		memset(value, 0, multSize(size, sizeof(uintmax)));
	}

	BitStream::~BitStream() {
		delete[] value;
	}

	void BitStream::append(uintmax val, uint8_t offset, uint8_t length) {
		length = min(length, innerSize);
		offset = min(offset, innerSize);

		if (length > innerSize - innerIndex) {
			if (innerIndex < innerSize) {
				value[index] |= catValue(val, offset, length, innerIndex);
				length -= subSize(innerSize, innerIndex);
			}

			index++;
			innerIndex = 0;

			if (index >= size) {
				uintmax* tmp = array_util::addToEnd(value, size, size / 2);
				delete[] value;
				value = tmp;
				size += size / 2;
			}
		}
		value[index] |= catValue(val, offset, length, innerIndex);
		innerIndex += length;
	}
	void BitStream::append(uintmax val, uint8_t offset, bool autoLength) {
		if (autoLength) {
			uint8_t length = multSize(8, sizeof(val));
			uintmax checker = 1ull << subSize(length, 1);
			while (length > 0) {
				if ((val & checker) == 0) {
					length = subSize(length, 1);
					checker = checker >> 1;
				} else {
					break;
				}
			}

			if (length > 0) {
				this->append(val, offset, length);
			}
		} else {
			this->append(val, offset, (uint8_t) (sizeof(val) * 8));
		}
	}
	void BitStream::append(uintmax val, uint8_t length) {
		this->append(val, 0, length);
	}

	void BitStream::append(uintmax val, bool autoLength) {
		this->append(val, 0, autoLength);
	}

	void BitStream::append(uintmax val) {
		this->append(val, true);
	}

	uintmax BitStream::get(uintmax index, uint8_t countOfBit) {
		if (countOfBit > innerSize) {
			throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT, "countOfBit is wrong. It must be < " + std::to_string(innerSize));
		}

		uintmax startBit = index * countOfBit;
		uintmax indexValue = startBit / innerSize;
		uintmax innerOffset = startBit % innerSize;
		

		if (indexValue > size 
			|| indexValue == size && innerOffset > innerIndex
			|| innerOffset + countOfBit > innerSize && indexValue + 1 >= size) {
			throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
		}

		if (innerOffset + countOfBit <= innerSize) {
			return catValue(value[indexValue], innerOffset, countOfBit, 0);
		} else {
			uintmax result = value[indexValue] >> innerOffset;
			countOfBit -= (innerSize - innerOffset);
			indexValue++;


			result |= catValue(value[indexValue], 0, countOfBit, subSize(innerSize, innerOffset));

			return result;
		}
		
	}

	void BitStream::set(uintmax val, uint8 offset, uint8 length, uintmax index, uint8_t countOfBit) {

		uintmax startBit = index * countOfBit;
		uintmax indexValue = startBit / innerSize;
		uintmax innerOffset = startBit % innerSize;

		if (indexValue > size
			|| indexValue == size && innerOffset > innerIndex
			|| innerOffset + countOfBit > innerSize && indexValue + 1 >= size
			|| length > countOfBit) {
			throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
		}

		uintmax valSize = addSize(innerOffset, countOfBit);
		if (valSize <= innerSize) {
			value[indexValue] = catValue(value[indexValue], 0, innerOffset, 0) | catValue(val, offset, length, innerOffset) | catValue(value[indexValue], valSize, innerSize, valSize);
		} else {
			value[indexValue] = catValue(value[indexValue], 0, innerOffset, 0) | catValue(val, offset, length, innerOffset);
			value[indexValue + 1] = catValue(value[indexValue + 1], subSize(valSize, innerSize), innerSize, subSize(valSize, innerSize)) | catValue(val, offset + subSize(innerSize, innerOffset), length - subSize(valSize, innerSize), 0);
		}
	}

	void BitStream::removeFromEnd(uintmax countOfBits) {
		if (countOfBits >= getCountOfBits()) {
			index = 0;
			innerIndex = 0;
			memset(value, 0, size);
		} else if (countOfBits > innerIndex) {
			value[index--] = 0;
			countOfBits = subSize(countOfBits, innerIndex);
			innerIndex = innerSize;
			int count = divSize(countOfBits, innerSize);
			countOfBits = subSize(countOfBits, multSize(count, innerSize));
			while (count > 0) {
				value[index--] = 0;
				count--;
			}

			if (countOfBits > 0) {
				removeFromEnd(countOfBits % innerSize);
			}
		} else {
			innerIndex -= countOfBits;
			uintmax tmp = 0;
			for (int i = 0; i < innerIndex; i++) {
				tmp += (1ull << i);
			}
			value[index] &= tmp;
		}
	}

	uintmax BitStream::getCountOfBits() {
		return sizeof(size) * 8 * index + innerIndex;
	}
	uintmax* BitStream::getArray() {
		return array_util::resize(value, size, size);
	}
	uint8_t* BitStream::getBytes() {
		uintmax resultSize = multSize(size, sizeof(uintmax));
		uint8_t* result = new uint8_t[resultSize];
		return nullptr;
	}
	void BitStream::operator<<(uintmax val) {
		this->append(val);
	}
	std::string const BitStream::toString(const uint8 countOfBit) {
		std::stringstream ss;
		uintmax bitSize = getCountOfBits();
		for (int i = 0; i < bitSize / countOfBit; i++) {
			ss << convert_util::UIntToChar(get(i, countOfBit), 255);
		}

		if (bitSize % countOfBit != 0) {
			ss << convert_util::UIntToChar(value[index] >> subSize(innerIndex, bitSize % countOfBit), 255);
		}
		return ss.str();
	}
}
