#include "LongNumber.h"

namespace livelib {
	namespace long_util {
		namespace conf_util {
			mint_t checkElement(const LongNumberConfiguration* conf, element_v value) {
				if (value > conf->maxValue) {
					return 1;
				} else if (value < conf->minValue) {
					return -1;
				} else {
					return 0;
				}
			}
		}

		element_v get(LongNumber * a, size_v index) {
			if (index >= a->size || index >= a->real_size) {
				return 0;
			} else {
				return a->value[index];
			}
		}

		void sum(LongNumber* a, LongNumber* b, LongNumber** out, const LongNumberConfiguration* conf, bool createNew) {
			using namespace conf_util;
			using namespace size_util;

			if (a->sign != b->sign) {
				if (a->sign) {
					sub(a, b, out, conf, createNew);
				} else {
					sub(b, a, out, conf, createNew);
				}
			}

			if (a->size < b->size) {
				std::swap(a, b);
			}

			if (createNew) {
				*out = new LongNumber();
				out[0]->real_size = size_util::addSize(a->size, 1);
				out[0]->value = new element_v[out[0]->real_size];
				out[0]->size = out[0]->real_size;
				out[0]->sign = a->sign;
			}

			element_v* _out = out[0]->value;

			for (size_v i = 0; i < b->size; i++) {
				_out[i] += get(a, i) + get(b, i);
				_out[i + 1] = 0;
				mint_t checkResult = checkElement(conf, _out[0]);
				if (checkResult == 1) {
					if (conf->useShifts) {
						_out[i + 1] << 1;
						_out[i + 1] += 1;
						_out[i] = ((element_v) _out[i] << 1) >> 1;
					} else {
						_out[i + 1] += _out[i] / conf->maxValue;
						_out[i] = _out[i] % conf->maxValue;
					}
				}
			}

			for (size_v i = b->size; i < a->size; i++) {
				_out[i] += get(a, i);
				_out[i + 1] = 0;
				mint_t checkResult = checkElement(conf, _out[0]);
				if (checkResult == 1) {
					if (conf->useShifts) {
						_out[i + 1] << 1;
						_out[i + 1] += 1;
						_out[i] = ((element_v) _out[i] << 1) >> 1;
					} else {
						_out[i + 1] += _out[i] / conf->maxValue;
						_out[i] = _out[i] % conf->maxValue;
					}
				}
			}

			size_v* size = &out[0]->size;
			while (_out[size_util::subSize(*size, 1)] == 0) {
				(*size)--;
			}
		}
		void sub(LongNumber * a, LongNumber * b, LongNumber ** out, const LongNumberConfiguration * conf, bool createNew) {
		}
	}
}