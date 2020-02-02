#pragma once
#include "size_util.h"

namespace livelib {
	namespace long_util {
		struct LongNumber {
			element_v* value;
			size_v size;
			size_v real_size;
			sign_t sign;
		};

		struct LongNumberConfiguration {
			element_v maxValue;
			element_v minValue;
			bool useShifts;

		public:
			LongNumberConfiguration(element_v minValue, element_v maxValue) {
				this->minValue = minValue;
				this->maxValue = maxValue;
			}

			LongNumberConfiguration(element_v minValue, element_v maxValue, bool useShifts) {
				this->minValue = minValue;
				this->maxValue = maxValue;
				this->useShifts = useShifts;
			}
		};

		namespace conf_util {
			mint_t checkElement(const LongNumberConfiguration* conf, element_v value);
		}

		element_v get(LongNumber* a, size_v index);
		void sum(LongNumber* a, LongNumber* b, LongNumber** out, const LongNumberConfiguration* conf, bool createNew);
		void sub(LongNumber* a, LongNumber* b, LongNumber** out, const LongNumberConfiguration* conf, bool createNew);
		void mult(LongNumber* a, LongNumber* b, LongNumber** out, const LongNumberConfiguration* conf, bool createNew);
		void div(LongNumber* a, LongNumber* b, LongNumber** out, const LongNumberConfiguration* conf, bool createNew);


		// Constains

		#ifdef _LPL_X32
		#endif //  _LPL_X32

		#ifdef _LPL_X64
		static const LongNumberConfiguration* unsignedBinConf = new LongNumberConfiguration(0, 0xFFFFFFFFull, true);
		static const LongNumberConfiguration* unsignedDecConf = new LongNumberConfiguration(0, 1000000000ull);
		#endif
	}

	
}