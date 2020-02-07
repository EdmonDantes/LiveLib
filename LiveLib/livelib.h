/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/
#pragma once
#include <string>
#include <chrono>

#ifndef LIVEPRODUCTIONLIB
#define LIVEPRODUCTIONLIB
#endif // !LIVEPRODUCTIONLIB

namespace livelib {

	#ifdef _WIN64
	#define _LPL_X64
	#else
	#ifdef _WIN32
	#define _LPL_X32
	#else
	#ifdef _WIN16
	#define _LPL_X16
	#else

	//Replace line after
	#error "Unsupport OS. Please add code for your OS" 

	//Example code for your OS:

	// #ifdef _OS_X16
	// #define _LPL_X16
	// #endif

	// #ifdef _OS_X32
	// #define _LPL_X32
	// #endif

	// #ifdef _OS_X64
	// #define _LPL_X64
	// #endif
	#endif


	#endif
	#endif
	
	//--------------For support systems------------\\
		//------- Types
		typedef uint8_t uint8;
		typedef int8_t int8;

		typedef uint16_t uint16;
		typedef int16_t int16;

		#ifdef _LPL_X16
		typedef uint16_t uintmax;
		typedef int16_t intmax;
		#endif

		#ifdef _LPL_X32
		typedef uint32_t uint32;
		typedef int32_t int32;

		typedef uint32_t uintmax;
		typedef uint32_t intmax;	
		#endif // _LPL_X32

		#ifdef _LPL_X64
		typedef uint32_t uint32;
		typedef int32_t int32;

		typedef uint64_t uint64;
		typedef int64_t int64;

		typedef uint64_t uintmax;
		typedef int64_t intmax;
		#endif // _LPL_X64

		#ifndef _LPL_MAX_PRECISION
		#define _LPL_MAX_PRECISION 0.000000001
		#endif // !_LPL_MAX_PRECISION



		//------- Error block
		static inline std::string createError(int code) {
			return "Live Production Lib: Error ¹" + std::to_string(code);
		}

		static inline std::string createError(std::string message) {
			return "Live Production Lib: Message: " + message;
		}

		static inline std::string createError(int code, std::string message) {
			return "Live Production Lib: Error ¹" + std::to_string(code) + ".\nMessage: " + message;
		}

		#define _LPL_ERROR_CODE_WRONG_ARGUMENT 1

		//------ Time`s functions
		#define getTime() chrono::steady_clock::now()
		#define getTimeNano(s, e) chrono::duration_cast<std::chrono::nanoseconds>((e) - (s)).count()
		#define getTimeMilli(s, e) chrono::duration_cast<std::chrono::milliseconds>((e) - (s)).count()
	
		//------ Arithmetically functions
		#define min(a, b) (((a) < (b)) ? (a) : (b))
		#define max(a, b) (((a) > (b)) ? (a) : (b))
}