#pragma once
#include "livelib.h"

namespace livelib {
	namespace array_util {

		template<typename T>
		T* addToStart(T* source, uintmax sourceSize, uintmax addSize) {
			T* result = new T[sourceSize + addSize];
			memcpy(result + addSize, source, sizeof(T) * sourceSize);
			memset(result, 0, sizeof(T) * addSize);
			return result;
		}

		template<typename T>
		T* addToEnd(T* source, uintmax sourceSize, uintmax addSize) {
			T* result = new T[sourceSize + addSize];
			memcpy(result, source, sizeof(T) * sourceSize);
			memset(result + sourceSize, 0, sizeof(T) * addSize);
			return result;
		}

		template<typename T>
		T* removeFromStart(T* source, uintmax sourceSize, uintmax removeSize) {
			if (removeSize >= sourceSize) {
				return new T[0];
			} else {
				T* result = new T[sourceSize - removeSize];
				memcpy(result, source + removeSize, sizeof(*result) * (sourceSize - removeSize));
				return result;
			}
		}

		template<typename T>
		T* removeFromEnd(T* source, uintmax sourceSize, uintmax removeSize) {
			if (removeSize > sourceSize) {
				return new T[0];
			} else {
				T* result = new T[sourceSize - removeSize];
				memcpy(result, source, sizeof(T) * (sourceSize - removeSize));
				return result;
			}
		}

		template<typename T>
		T* resize(T* source, uintmax sourceSize, uintmax resultSize) {
			if (resultSize > sourceSize) {
				return addToEnd(source, sourceSize, resultSize - sourceSize);
			} else if (resultSize < sourceSize) {
				return removeFromEnd(source, sourceSize, sourceSize - resultSize);
			} else {
				T* result = new T[sourceSize];
				memcpy(result, source, sizeof(T) * sourceSize);
				return result;
			}
		}
	}

}