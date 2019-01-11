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

	BigInteger::BigInteger(size_p* value, size_v size, bool isNegate = false) {
		this->value = value;
		this->real_size = this->size = size;
		this->isNegate = isNegate;
	}

	BigInteger::BigInteger(size_p* value, size_v size, size_v real_size, bool isNegate = false) {
		this->value = value;
		this->size = size;
		this->real_size = real_size;
		this->isNegate = isNegate;
	}

	size_p* BigInteger::_sum(size_p* a, size_v a_len, size_p* b, size_v b_len) {
		size_v min_len = a_len <= b_len ? a_len : b_len;
		size_v max_len = a_len <= b_len ? b_len : a_len;
		size_p* min_number = a_len < b_len ? a : b;
		size_p* max_number = a_len < b_len ? b : a;

		size_v out_len = max_len + 1;

		size_p* out = new size_p[out_len];
		out[0] = 0;

		for (size_v i = 0; i < min_len; i++) {
			size_p tmp = min_number[i] + max_number[i];
			out[i] += tmp % BigInteger::max_size_of_part;
			out[i + 1] = tmp / BigInteger::max_size_of_part;
		}

		for (size_v i = min_len; i < max_len; i++) {
			out[i] += max_number[i];
			out[i + 1] = out[i] / BigInteger::max_size_of_part;
			out[i] %= BigInteger::max_size_of_part;
		}

		return out;
	}

	size_p* BigInteger::_sub(size_p* a, size_v a_len, size_p* b, size_v b_len) {
		size_v min_len;
		size_v max_len;
		size_p* min_number;
		size_p* max_number;

		if (a_len < b_len || (a_len == b_len && a[a_len - 1] < b[b_len - 1])) {
			min_len = a_len;
			max_len = b_len;
			min_number = a;
			max_number = b;
		}
		else {
			min_len = b_len;
			max_len = a_len;
			min_number = b;
			max_number = a;
		}

		size_p* out = new size_p[max_len + 1];
		out[0] = 0;

		for (size_v i = 0; i < min_len; i++) {
			out[i] += max_number[i] - min_number[i];

			out[i + 1] = 0;

			while (out[i] > BigInteger::max_size_of_part) {
				out[i + 1] -= 1;
				out[i] += BigInteger::max_size_of_part;
			}
		}

		for (size_v i = 0; i < max_len; i++) {
			out[i] += max_number[i];
			out[i + 1] = 0;
			while (out[i] > BigInteger::max_size_of_part) {
				out[i + 1] -= 1;
				out[i] += BigInteger::max_size_of_part;
			}
		}

		return out;
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

	BigInteger::BigInteger(const std::string& str) {
		if (str.length() < 1) throw LIVE_LIB_ERROR_WRONG_STRING;

		int str_index = 0;
		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;

		this->real_size = this->size = (str.length() - str_index) / this->max_length_of_part + ((str.length() - str_index) % this->max_length_of_part > 0 ? 1 : 0);

		this->value = new size_p[this->real_size];

		for (int j = 0; str_index < str.length(); str_index++) {
			if (j >= this->max_length_of_part) j = 0;
			if (j == 0) this->value[str_index / this->max_length_of_part] = 0;

			this->value[str_index / this->max_length_of_part] += (str[str_index] - '0') * pow(10, j++);
		}

	}

	BigInteger::BigInteger(const char* str) {
		int str_length = strlen(str);

		if (str_length < 1) throw LIVE_LIB_ERROR_WRONG_STRING;

		int str_index = 0;
		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;

		this->real_size = this->size = (str_length - str_index) / this->max_length_of_part + ((str_length - str_index) % this->max_length_of_part > 0 ? 1 : 0);

		this->value = new size_p[this->real_size];

		length_p j = 0;
		for (size_v i = 0; i < str_length - str_index; i++) {
			if (j >= this->max_length_of_part) j = 0;

			if (j == 0) this->value[i / this->max_length_of_part] = 0;

			this->value[i / this->max_length_of_part] += (str[str_length - i - 1] - '0') * pow(10, j++);
		}
	}

	BigInteger& BigInteger::operator + (const BigInteger& b) {
		if (this->size < 1 || b.size < 1) return *(new BigInteger());
		
		if (!this->isNegate && !b.isNegate) {
			size_p* val = _sum(this->value, this->size, b.value, b.size);
			size_v val_len = (this->size > b.size ? this->size : b.size) + 1;
			if (val[val_len - 1] == 0)
				return *(new BigInteger(val, val_len - 1, val_len, false));
			else
				return *(new BigInteger(val, val_len, false));
		}
		else if (!this->isNegate && b.isNegate) {
			size_p* val = _sub(this->value, this->size, b.value, b.size);
			size_v val_len = (this->size > b.size ? this->size : b.size) + 1;
			if (val[val_len - 1] == 0)
				return *(new BigInteger(val, val_len - 1, val_len, false));
			else {
				while (val[val_len - 1] > BigInteger::max_size_of_part) val[val_len - 1] += BigInteger::max_size_of_part;
				return *(new BigInteger(val, val_len, true));
			}
		}
		else if (this->isNegate && !b.isNegate) {
			size_p* val = _sub(b.value, b.size, this->value, this->size);
			size_v val_len = (this->size > b.size ? this->size : b.size) + 1;
			if (val[val_len - 1] == 0)
				return *(new BigInteger(val, val_len - 1, val_len, false));
			else {
				while (val[val_len - 1] > BigInteger::max_size_of_part) val[val_len - 1] += BigInteger::max_size_of_part;
				return *(new BigInteger(val, val_len, true));
			}
		}
		else if (this->isNegate && b.isNegate) {
			size_p* val = _sum(this->value, this->size, b.value, b.size);
			size_v val_len = (this->size > b.size ? this->size : b.size) + 1;
			if (val[val_len - 1] == 0)
				return *(new BigInteger(val, val_len - 1, val_len, true));
			else
				return *(new BigInteger(val, val_len, true));
		}
		else return *(new BigInteger());
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

	std::string& BigInteger::toString() {

		std::stringstream* ret = new std::stringstream();
		if (this->size < 0) *ret << "NaN";
		else {

			if (this->isNegate) *ret << "-";

			for (size_v i = 0; i < this->size; i++) {
				std::string tmp = std::to_string(this->value[this->size - i - 1]);
				while (tmp.length() < BigInteger::max_length_of_part && i != 0) tmp = "0" + tmp;
				*ret << tmp;
			}
		}

		std::string* _ret = new std::string(ret->str());
		delete ret;
		return *_ret;
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

	BigInteger& BigInteger::random(size_v length = 20){
		std::srand(std::time(NULL));
		std::string ret;
		while (ret.length() < length) {
			ret.append(std::to_string(rand()));
		}

		return *(new BigInteger(ret.substr(0, length)));
	}
};