#pragma once
#include "livelib.h"

namespace livelib {
	class BitStream {
	private:
		static const uint8_t innerSize = sizeof(uintmax) * 8;

		uintmax* value;
		uintmax size;
		uintmax index;
		uint8_t innerIndex;

		inline uintmax catValue(uintmax value, uint8 offset, uint8 length, uint8 endShift);
	public:
		BitStream();
		BitStream(uintmax countOfBits);

		~BitStream();

		void append(uintmax val, uint8_t offset, uint8_t length);
		void append(uintmax val, uint8_t offset, bool autoLength);
		void append(uintmax val, uint8_t length);
		void append(uintmax val, bool autoLength);
		void append(uintmax val);

		uintmax get(uintmax index, uint8_t countOfBit);

		void set(uintmax value, uint8 offset, uint8 length, uintmax index, uint8_t countOfBit);

		void removeFromEnd(uintmax countOfBits);

		uintmax getCountOfBits();
		uint8_t* getBytes();

		uintmax* getArray();
		uintmax* toArray();

		void operator << (uintmax val);

		std::string const toString(uint8 countOfBit);
	};
}