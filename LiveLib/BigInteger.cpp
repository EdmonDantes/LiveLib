/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/
#include "BigInteger.h"
#include <ctime>
#include <random>
#include <sstream>

namespace livelib {

	//------------------Private Section------------\\

	size_p BigInteger::max_dec_size_of_part = floor(pow(10, floor(log10(BigInteger::max_size_of_part))));

	BigInteger::BigInteger(size_p* value, size_v size, size_v real_size, bool isNegate = false) {
		this->value = value;
		this->size = size;
		this->real_size = real_size;
		this->isNegate = isNegate;
	}

	void BigInteger::_sum(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size) {
		size_v min_size;
		size_v max_size;
		size_p* min_number;
		size_p* max_number;

		if (a_size < b_size) {
			min_size = a_size;
			max_size = b_size;
			min_number = a;
			max_number = b;
		}
		else {
			min_size = b_size;
			max_size = a_size;
			min_number = b;
			max_number = a;
		}

		size_p* _out = new size_p[max_size + 1];
		_out[0] = 0;

		for (size_v i = 0; i < min_size; i++) {
			_out[i] += min_number[i] + max_number[i];
			_out[i + 1] = _out[i] >> BigInteger::bit_shift;
			_out[i] = _out[i] & BigInteger::max_size_of_part;
		}

		for (size_v i = min_size; i < max_size; i++) {
			_out[i] += max_number[i];
			_out[i + 1] = _out[i] >> BigInteger::bit_shift;
			_out[i] = _out[i] & BigInteger::max_size_of_part;
		}

		*out = _out;
		*out_real_size = max_size + 1;
		while (_out[max_size] == 0) max_size--;
		*out_size = max_size + 1;
	}

	void BigInteger::_sub(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size) {
		size_v min_size;
		size_v max_size;

		if (a_size < b_size || (a_size == b_size && a[a_size - 1] < b[b_size - 1])) {
			min_size = a_size;
			max_size = b_size;
		}
		else {
			min_size = b_size;
			max_size = a_size;
		}

		size_p* _out = new size_p[max_size + 1];
		_out[0] = 0;

		for (size_v i = 0; i < min_size; i++) {
			_out[i] += a[i] - b[i];
			_out[i + 1] = 0;

			while (_out[i] > BigInteger::max_size_of_part) {
				_out[i + 1] -= 1;
				_out[i] += BigInteger::max_size_of_part;
			}
		}

		for (size_v i = min_size; i < max_size; i++) {
			if (a_size == min_size) _out[i] -= b[i];
			else _out[i] += a[i];
			_out[i + 1] = 0;
			while (_out[i] > BigInteger::max_size_of_part) {
				_out[i + 1] -= 1;
				_out[i] += BigInteger::max_size_of_part;
			}
		}

		*out = _out;
		*out_size = *out_real_size = max_size + 1;
	}


	//------------------Public Section------------\\
		
	BigInteger::BigInteger() {
		this->size = 0;
		this->real_size = 0;
		this->value = 0;
		this->isNegate = false;
	}

	BigInteger::BigInteger(const BigInteger& b) {
		this->isNegate = b.isNegate;

		this->real_size = this->size = b.size;

		this->value = new size_p[this->real_size];

		for (size_v i = 0; i < b.size; i++) {
			this->value[i] = b.value[i];
		}
	}

	BigInteger::BigInteger(std::string& str) {
		if (str.length() < 1) throw LIVE_LIB_ERROR_WRONG_STRING;

		int str_index = 0;
		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;

		size_v size = (str.length() - str_index) / (BigInteger::max_length_of_part - 1) + ((str.length() - str_index) % (BigInteger::max_length_of_part - 1) > 0 ? 1 : 0);

		size_p* value = new size_p[size];

		size_v j = 0;
		size_p number = 0;
		length_p number_length = 0;
		for (int i = 0; i < str.length() - str_index; i++) {
			size_p tmp = number + (str[str.length() - i - 1] - '0') * pow(10, number_length);
			if (tmp < BigInteger::max_size_of_part && number_length < BigInteger::max_length_of_part) {
				number = tmp;
				number_length++;
			}
			else {
				value[j++] = number;
				number_length = 0;
				number = (str[str.length() - i - 1] - '0') * pow(10, number_length);
			}
		}

		if (number > 0) {
			value[j++] = number;
		}

		this->value = value;
		this->size = j;
		this->real_size = size;
	}

	BigInteger::BigInteger(const char* str) {
		int str_length = strlen(str);

		if (str_length < 1) throw LIVE_LIB_ERROR_WRONG_STRING;

		int str_index = 0;
		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;

		size_v size = (str_length - str_index) / (BigInteger::max_length_of_part - 1) + ((str_length - str_index) % (BigInteger::max_length_of_part - 1) > 0 ? 1 : 0);

		size_p* value = new size_p[size];

		size_v j = 0;
		size_p number = 0;
		length_p number_length = 0;
		for (int i = 0; i < str_length - str_index; i++) {
			size_p tmp = number + (str[str_length - i - 1] - '0') * pow(10, number_length);
			if (tmp < BigInteger::max_size_of_part && number_length < BigInteger::max_length_of_part) {
				number = tmp;
				number_length++;
			}
			else {
				value[j++] = number;
				number_length = 0;
				number = (str[str_length - i - 1] - '0') * pow(10, number_length);
			}
		}

		if (number > 0) {
			value[j++] = number;
		}

		this->value = value;
		this->size = j;
		this->real_size = size;
	}

	BigInteger::~BigInteger() {
		if (this->value != 0) delete[] this->value;
	}

	BigInteger BigInteger::operator + (const BigInteger& b) {
		if (this->size < 1 || b.size < 1) return BigInteger();
		
		size_p* out = 0;
		size_v out_size = 0;
		size_v out_real_size = 0;
		bool isNegate = false;

		if (!this->isNegate && !b.isNegate) {
			_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
		}
		else if (!this->isNegate && b.isNegate) {
			_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			if (out[out_size - 1] == 0)
				out_size--;
			else {
				while (out[out_size - 1] > BigInteger::max_size_of_part) out[out_size - 1] += BigInteger::max_size_of_part;
				isNegate = true;
			}
		}
		else if (this->isNegate && !b.isNegate) {
			_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			if (out[out_size - 1] == 0) {
				out_size--;
				isNegate = true;
			} else {
				while (out[out_size - 1] > BigInteger::max_size_of_part) out[out_size - 1] += BigInteger::max_size_of_part;
				
			}
		}
		else if (this->isNegate && b.isNegate) {
			_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			isNegate = true;
		}
		else return BigInteger();

		return BigInteger(out, out_size, out_real_size, isNegate);
	}

	BigInteger BigInteger::operator - (const BigInteger& b) {
		if (this->size < 1 || b.size < 1) return BigInteger();

		size_p* out = 0;
		size_v out_size = 0;
		size_v out_real_size = 0;
		bool isNegate = false;
		if (!this->isNegate && !b.isNegate) {
			_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			if (out[out_size - 1] == 0)
				out_size--;
			else {
				while (out[out_size - 1] > BigInteger::max_size_of_part) out[out_size - 1] += BigInteger::max_size_of_part;
				isNegate = true;
			}
		}
		else if (!this->isNegate && b.isNegate) {
			_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
		}
		else if (this->isNegate && !b.isNegate) {
			_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
		}
		else if (this->isNegate && b.isNegate) {
			_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			if (out[out_size - 1] == 0) {
				out_size--;
				isNegate = true;
			}
			else {
				while (out[out_size - 1] > BigInteger::max_size_of_part) out[out_size - 1] += BigInteger::max_size_of_part;
			}
		}
		else return BigInteger();

		return BigInteger(out, out_size, out_real_size, isNegate);
	}

	BigInteger& BigInteger::operator = (const BigInteger& b) {
		if (this->real_size < (this->size = b.size)) {
			if (this->value != 0) delete[] value;

			this->real_size = this->size;
			value = new size_p[this->real_size];
		}

		this->isNegate = b.isNegate;

		for (size_v i = 0; i < this->size; i++) {
			this->value[i] = b.value[i];
		}

		return *this;
	}

	std::string BigInteger::toString() {

		std::stringstream* ret = new std::stringstream();
		if (this->size < 0) *ret << "NaN";
		else {

			if (this->isNegate && (this->size > 1 || this->value[0] != 0)) *ret << "-";

			size_p number = 0;
			for (size_v i = 0; i < this->size; i++) {
				size_p tmp = this->value[this->size - i - 1] + number;
				number = tmp / BigInteger::max_dec_size_of_part;
				tmp = tmp % BigInteger::max_dec_size_of_part;

				std::string add = std::to_string(tmp);
				if (add.length() < (BigInteger::max_length_of_part - 1))
					while (add.length() < BigInteger::max_length_of_part && i != 0) add = "0" + add;
				*ret << add;
			}

			if (number > 0) *ret << number;
		}
		std::string _ret = std::string(ret->str());
		delete ret;
		return _ret;
	}

	bool BigInteger::operator < (const BigInteger& b) {
		if (this->isNegate != b.isNegate) return this->isNegate && !b.isNegate;
		if (this->size != b.size) return this->isNegate && b.isNegate && this->size > b.size || !this->isNegate && !b.isNegate && this->size < b.size;

		for (size_v i = 0; i < this->size; i++) {
			if (this->value[i] > b.value[i]) return this->isNegate;
		}

		return !this->isNegate;
	}

	bool BigInteger::operator > (const BigInteger& b) {
		if (this->isNegate != b.isNegate) return !this->isNegate && b.isNegate;
		if (this->size != b.size) return this->isNegate && b.isNegate && this->size < b.size || !this->isNegate && !b.isNegate && this->size > b.size;

		for (size_v i = 0; i < this->size; i++) {
			if (this->value[i] < b.value[i]) return this->isNegate;
		}

		return !this->isNegate;
	}

	bool BigInteger::operator <= (const BigInteger& b) {
		return !((*this) > b);
	}

	bool BigInteger::operator >= (const BigInteger& b) {
		return !((*this) < b);
	}

	bool BigInteger::operator == (const BigInteger& b) {
		if (this->isNegate != b.isNegate || this->size != b.size) return false;

		for (size_v i = 0; i < this->size; i++) {
			if (this->value[i] != b.value[i]) return false;
		}

		return true;
	}

	bool BigInteger::operator != (const BigInteger& b) {
		return !((*this) == b);
	}

	bool BigInteger::isNegative() {
		return this->isNegate;
	}

	bool BigInteger::isPositive() {
		return !this->isNegate;
	}

	bool BigInteger::isNaN() {
		return this->size == 0;
	}

	BigInteger BigInteger::random(size_v length = 20){
		std::srand(std::time(NULL));

		std::stringstream ret;
		size_v number_length = 0;

		while (number_length < length) {
			std::string tmp = std::to_string(rand());
			number_length += tmp.length();
			ret << tmp;
		}
		std::string _ret = ret.str().substr(0, length);
		return BigInteger(_ret);
	}
};