/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/
#include "BigInteger.h"
#include <ctime>
#include <random>
#include <sstream>

namespace livelib {

	//------------------Protected Section------------\\

	bool BigInteger::null_var_for_static_block = (BigInteger::static_block(), true);
	
	void BigInteger::static_block() {
		std::srand(std::time(NULL));
	}

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
			_out[i + 1] = _out[i] / BigInteger::max_size_of_part;
			_out[i] = _out[i] % BigInteger::max_size_of_part;
		}

		for (size_v i = min_size; i < max_size; i++) {
			_out[i] += max_number[i];
			_out[i + 1] = _out[i] / BigInteger::max_size_of_part;
			_out[i] = _out[i] % BigInteger::max_size_of_part;
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

			while (_out[i] < 0){
				_out[i + 1] -= 1;
				_out[i] += BigInteger::max_size_of_part;
			}
		}

		for (size_v i = min_size; i < max_size; i++) {
			if (a_size == min_size) _out[i] -= b[i];
			else _out[i] += a[i];
			_out[i + 1] = 0;

			while (_out[i] < 0) {
				_out[i + 1] -= 1;
				_out[i] += BigInteger::max_size_of_part;
			}
		}

		*out = _out;
		*out_size = *out_real_size = max_size + 1;
	}

	void BigInteger::_multStandart(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size) {
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

		size_v size = a_size + b_size + 1;
		size_p* _out = new size_p[size];
		
		memset(_out, 0, sizeof(size_p) * size);

		for (size_v i = 0; i < min_size; i++)
			for (size_v j = 0; j < max_size; j++) {
				_out[i + j] += min_number[i] * max_number[j];
				_out[i + j + 1] += _out[i + j] / BigInteger::max_size_of_part;
				_out[i + j] = _out[i + j] % BigInteger::max_size_of_part;
			}

		*out = _out;
		*out_real_size = size;
		while (_out[size - 1] == 0 && size > 1) size--;
		*out_size = size;
	}

	void BigInteger::_multInMiddle(size_p* a, size_v a_size, size_p* b, size_v b_size, size_p** out, size_v* out_size, size_v* out_real_size) {
		size_v max_size = a_size > b_size ? a_size : b_size;

		if (max_size <= 325) return _multStandart(a, a_size, b, b_size, out, out_size, out_real_size);

		size_v middle = max_size / 2;
		
		size_p* A1 = new size_p[middle];
		size_p* A2 = new size_p[max_size - middle];
		size_p* B1 = new size_p[middle];
		size_p* B2 = new size_p[max_size - middle];

		for (int i = 0; i < max_size - middle; i++) {
			A2[i] = i < a_size ? a[i] : 0;
			B2[i] = i < b_size ? b[i] : 0;
		}

		for (int i = 0; i < middle; i++) {
			A1[i] = (i + middle < a_size ? a[i + middle] : 0);
			B1[i] = (i + middle < b_size ? b[i + middle] : 0);
		}
		
		size_p* P1;
		size_v P1_size;
		size_v P1_real_size;
		_multInMiddle(A1, middle, B1, middle, &P1, &P1_size, &P1_real_size);
		
		size_p* P2;
		size_v P2_size;
		size_v P2_real_size;
		_multInMiddle(A2, max_size - middle, B2, max_size - middle, &P2, &P2_size, &P2_real_size);
		
		size_p* Xlr = new size_p[middle];
		size_p* Ylr = new size_p[middle];
		
		for (size_v i = 0; i < middle; i++) {
			Xlr[i] = (i < max_size - middle ? A2[i] : 0) + A1[i];
			Ylr[i] = (i < max_size - middle ? B2[i] : 0) + B1[i];
		}
		
		size_p* P3;
		size_v P3_size;
		size_v P3_real_size;
		_multInMiddle(Xlr, middle, Ylr, middle, &P3, &P3_size, &P3_real_size);
		
		*out = new size_p[2 * max_size];



		for (size_v i = 0; i < max_size; i++) {
			(*out)[i] = i < P2_size ? P2[i] : 0;
		}
		
		for (size_v i = max_size; i < 2 * max_size; i++) {
			(*out)[i] = i - max_size < P1_size ? P1[i - max_size] : 0;
		}
		
		for (size_v i = middle; i < max_size + middle; i++) {
			(*out)[i] += (i - middle < P3_size ? P3[i - middle] : 0) - (i - middle < P2_size ? P2[i - middle] : 0) - (i - middle < P1_size ? P1[i - middle] : 0);
		}

		
		*out_size = *out_real_size = 2 * max_size;
		for (size_v i = 0; i < *out_size - 1; i++) {
			while ((*out)[i] < 0) {
				(*out)[i + 1] -= 1;
				(*out)[i] += BigInteger::max_size_of_part;
			}
			(*out)[i + 1] += (*out)[i] / BigInteger::max_size_of_part;
			(*out)[i] = (*out)[i] % BigInteger::max_size_of_part;
		}

		while ((*out)[(*out_size) - 1] == 0) (*out_size)--;

		delete[] A1;
		delete[] A2;
		delete[] B1;
		delete[] B2;
		delete[] P1;
		delete[] P2;
		delete[] P3;
		delete[] Xlr;
		delete[] Ylr;
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

		size_v size = (str.length() - str_index) / BigInteger::max_length_of_part + ((str.length() - str_index) % BigInteger::max_length_of_part > 0 ? 1 : 0);

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
				number = (str[str.length() - i - 1] - '0') * pow(10, number_length++);
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

		size_v size = (str_length - str_index) / BigInteger::max_length_of_part + ((str_length - str_index) % BigInteger::max_length_of_part > 0 ? 1 : 0);

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
				number = (str[str_length - i - 1] - '0') * pow(10, number_length++);
			}
		}

		if (number > 0 || j < 1) {
			value[j++] = number;
		}

		this->value = value;
		this->size = j;
		this->real_size = size;
	}

	BigInteger::~BigInteger() {
		if (this->value != 0) delete[] this->value;
	}

	BigInteger BigInteger::sum(const BigInteger& b, int type) {
		switch (type) {
		default:
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
				if (out[out_size - 1] > BigInteger::max_size_of_part) {
					isNegate = true;
					out_size--;
				}
				while (out[out_size - 1] == 0) out_size--;
			}
			else if (this->isNegate && !b.isNegate) {
				_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
				if (out[out_size - 1] <= BigInteger::max_size_of_part) {
					isNegate = true;
					out_size--;
				}
				while (out[out_size - 1] == 0) out_size--;
			}
			else if (this->isNegate && b.isNegate) {
				_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
				isNegate = true;
			}
			else return BigInteger();

			return BigInteger(out, out_size, out_real_size, isNegate);
			break;
		}
	} 

	BigInteger BigInteger::sub(const BigInteger& b, int type) {
		switch (type) {
		default:
			if (this->size < 1 || b.size < 1) return BigInteger();

			size_p* out = 0;
			size_v out_size = 0;
			size_v out_real_size = 0;
			bool isNegate = false;
			if (!this->isNegate && !b.isNegate) {
				_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
				if (out[out_size - 1] > BigInteger::max_size_of_part) {
					isNegate = true;
					out_size--;
				}
				while (out[out_size - 1] == 0) out_size--;
			}
			else if (!this->isNegate && b.isNegate) {
				_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			}
			else if (this->isNegate && !b.isNegate) {
				_sum(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			}
			else if (this->isNegate && b.isNegate) {
				_sub(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
				if (out[out_size - 1] <= BigInteger::max_size_of_part) {
					isNegate = true;
					out_size--;
				}
				while (out[out_size - 1] == 0) out_size--;
			}
			else 
				return BigInteger();

			return BigInteger(out, out_size, out_real_size, isNegate);
			break;
		}
	}

	BigInteger BigInteger::mult(const BigInteger& b, int type) {
		if (this->size < 1 || b.size < 1) return BigInteger();

		size_p* out = 0;
		size_v out_size = 0;
		size_v out_real_size = 0;
		switch (type) {
		case KABYC_MULT:
			_multInMiddle(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			break;
		default:
			_multStandart(this->value, this->size, b.value, b.size, &out, &out_size, &out_real_size);
			break;
		}

		return BigInteger(out, out_size, out_real_size, this->isNegate != b.isNegate);
	}

	BigInteger BigInteger::operator + (const BigInteger& b) {
		return sum(b, STD_SUM);
	}

	BigInteger BigInteger::operator - (const BigInteger& b) {
		return sub(b, STD_SUB);
	}

	BigInteger BigInteger::operator * (const BigInteger& b) {
		return mult(b, KABYC_MULT);
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

		std::string ret = std::string("");
		if (this->size < 0) ret.append("NaN");
		else {

			if (this->isNegate && (this->size > 1 || this->value[0] != 0)) ret.append("-");

			for (size_v i = 0; i < this->size; i++) {
				std::string tmp = std::to_string(this->value[this->size - i - 1]);
				while (tmp.length() < BigInteger::max_length_of_part && i != 0) {
					tmp = "0" + tmp;
				}
				ret.append(tmp);
			}
		}
		return ret;
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