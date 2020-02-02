#include "size_util.h"

namespace livelib {
	namespace size_util {
		size_v addSize(size_v a, size_v b) {
			size_v result = a + b;
			if (result < a || result < b) {
				throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
			} else {
				return result;
			}
		}

		size_v subSize(size_v a, size_v b) {
			size_v result = a - b;
			if (result > a) {
				throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
			} else {
				return result;
			}
		}

		size_v multSize(size_v a, size_v b) {
			size_v result = a * b;
			if (result < a || result < b) {
				throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
			} else {
				return result;
			}
		}

		size_v divSize(size_v a, size_v b) {
			size_v result = a / b;
			if (result > a) {
				throw createError(_LPL_ERROR_CODE_WRONG_ARGUMENT);
			} else {
				return result;
			}
		}
	}
}