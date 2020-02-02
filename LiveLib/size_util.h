#pragma once
#include "livelib.h"

namespace livelib {
	typedef uintmax size_v;
	typedef uintmax element_v;
	typedef bool sign_t;
	typedef int8_t mint_t;

	namespace size_util {
		size_v addSize(size_v a, size_v b);
		size_v subSize(size_v a, size_v b);
		size_v multSize(size_v a, size_v b);
		size_v divSize(size_v a, size_v b);
	}
}