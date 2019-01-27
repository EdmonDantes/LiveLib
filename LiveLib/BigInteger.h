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
	private:
#ifdef _X64
		const static size_p max_size_of_part = 0xfffffff;
		const static length_p max_length_of_part = 10;
		const static length_p bit_shift = 32;
		
#else
		const static size_p max_size_of_part = 0xffff;
		const static length_p max_length_of_part = 5;
		const static length_p bit_shift = 16;
#endif

		static size_p max_dec_size_of_part;

		size_p* value = 0; // Array for save data about number
		size_v size = 0; // Number`s size
		size_v real_size = 0; // Array`s size. For lesser use memory
		bool isNegate = false; // True if number less than 0

		BigInteger(size_p* value, size_v size, size_v real_size, bool isNegate);

		/*
			_sum(a, a_len, b, b_len)
			Added number @a with length @a_len and number @b with length @b_len
			@a_len and @b_len must be > 0
			Return number with length = max(@a_len, @b_len) + 1
		*/
		static void _sum(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

		/*
			_minus(a, a_len, b, b_len)
			Substruct number @a with length @a_len and number @b with length @b_len
			@a_len and @b_len must be > 0
			Return number with length = max(@a_len, @b_len) + 1
			If @a > @b return @a - @b else return @b - @a
		*/
		static void _sub(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size);

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
		BigInteger& operator * (const BigInteger&);
		BigInteger& operator / (const BigInteger&);
		BigInteger& operator % (const BigInteger&);
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
