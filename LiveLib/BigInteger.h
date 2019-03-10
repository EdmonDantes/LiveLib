/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/
#pragma once
#ifndef __LiveLib__
#include "livelib.h"
#endif // !LIVELIB
#ifndef __BigInteger_LL__
#define __BigInteger_LL__

namespace livelib {
	class BigInteger {
	protected:
#ifdef _X64
		const static size_p max_size_of_part = 1000000000;
		const static length_p max_length_of_part = 9;
#else
		const static size_p max_size_of_part = 10000;
		const static length_p max_length_of_part = 4;
#endif
		size_p* value = 0; // Array for save data about number
		size_v size = 0; // Number`s size
		size_v real_size = 0; // Array`s size. For lesser use memory
		bool isNegate = false; // True if number less than 0

		BigInteger(size_p* value, size_v size, size_v real_size, bool isNegate);

		/*
			_sum(a, a_len, b, b_len)
			Added number @a with size @a_size and number @b with size @b_size
			@a_size and @b_size must be > 0
			Write result to @out with size @out_size with real size @out_real_size
			Return number with size = max(@a_size, @b_size) + 1

			Algorith complexity = O(n); n = max(@a_size, @b_size)
		*/
		static void _sum(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

		/*
			_minus(a, a_len, b, b_len)
			Substruct number @a with size @a_size and number @b with size @b_size
			@a_size and @b_size must be > 0
			Write result to @out with size @out_size with real size @out_real_size
			Return number with size = max(@a_size, @b_size) + 1

			Algorith complexity = O(n); n = max(@a_size, @b_size)
		*/
		static void _sub(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

		/*
			_multNative(a, a_len, b, b_len)
			Multiply number @a with size @a_size and number @b with size @b_size
			@a_size and @b_size must be > 0
			Write result to @out with size @out_size with real size @out_real_size
			Return number with size = @a_size + @b_size + 1

			Algorith complexity = O(n * m); n = @a_size; m = @b_size
		*/
		static void _multStandart(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

		/*
			_multKarab(a, a_len, b, b_len)
			Multiply number @a with size @a_size and number @b with size @b_size
			@a_size and @b_size must be > 0
			Write result to @out with size @out_size with real size @out_real_size
			Return number with size = @a_size + @b_size + 1

			Algorith complexity = O(n^(log_2(3))); n = max(@a_size, @b_size);
		*/
		static void _multKarab(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

	public:
		BigInteger(); // Create NaN number

		BigInteger(const BigInteger&); // Copy constructor

		// Constructor for create numbers
		BigInteger(std::string&);
		BigInteger(const char*);

		~BigInteger();
		

		// Arithmetic operators
		BigInteger operator + (const BigInteger&);
		BigInteger operator - (const BigInteger&);
		BigInteger operator * (const BigInteger&);
		BigInteger operator / (const BigInteger&);
		BigInteger operator % (const BigInteger&);
		BigInteger& operator += (const BigInteger&);
		BigInteger& operator -= (const BigInteger&);
		BigInteger& operator *= (const BigInteger&);
		BigInteger& operator /= (const BigInteger&);
		BigInteger& operator %= (const BigInteger&);
		BigInteger& operator ++ (int);
		BigInteger& operator ++ ();
		BigInteger& operator -- (int);
		BigInteger& operator -- ();
		BigInteger& operator = (const BigInteger&);

		//Logical operators
		bool operator < (const BigInteger& b);
		bool operator > (const BigInteger& b);
		bool operator <= (const BigInteger& b);
		bool operator >= (const BigInteger& b);
		bool operator == (const BigInteger& b);
		bool operator != (const BigInteger& b);

		// Method return status of number
		bool isNaN();
		bool isPositive();
		bool isNegative();

		// Return number
		std::string toString();

		//Create random number
		static BigInteger random(size_v length);
	};
}
#endif
