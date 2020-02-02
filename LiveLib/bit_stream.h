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

	public:
		BitStream();
		BitStream(uintmax countOfBits);

		void append(uintmax val, uint8_t offset, uint8_t length);
		void append(uintmax val, uint8_t offset, bool autoLength);
		void append(uintmax val, uint8_t length);
		void append(uintmax val, bool autoLength);
		void append(uintmax val);

		uintmax get(uintmax index, uint8_t countOfBit);

		void removeFromEnd(uintmax countOfBits);

		uintmax getCountOfBits();
		uintmax* getArray();
		uint8_t* getBytes();

		void operator << (uintmax val);
	};
}