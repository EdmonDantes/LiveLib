/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/
#pragma once
#ifndef __LiveLib__
#include <string>


namespace livelib {

#define __LiveLib__

#ifdef _WIN64
#define _X64
	typedef long long size_p; // size of values part
	typedef unsigned long long size_v; // size of value

	#define SIZE_V_MAX ULLONG_MAX
#else
#ifdef _WIN32
#define _X32
	typedef long size_p; // size of values part
	typedef unsigned long size_v; // size of value

	#define SIZE_V_MAX ULONG_MAX
#endif // _WIN32 
#endif // _WIN64





#ifdef __linux__
	#error This library can`t work on linux system
#endif
	
	//--------------For all systems------------\\
	
	typedef int8_t length_p;
	#define LIVE_LIB_ERROR_WRONG_STRING "Live Lib: ERROR => Wrong string"
	#define getTime() chrono::steady_clock::now()
	#define getTimeN(s, e) chrono::duration_cast<std::chrono::nanoseconds>(e - s).count()
	#define getTimeM(s, e) chrono::duration_cast<std::chrono::milliseconds>(e - s).count()
}
#endif