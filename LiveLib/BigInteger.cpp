///*
//Copyright © 2019 Ilya Loginov. All rights reserved.
//Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
//*/
//
//#include "BigInteger.h"
//#include <ctime>
//#include <random>
//#include <sstream>
//
//namespace livelib {
//
//	//------------------Protected Section------------\\
//
//	bool BigInteger::null_var_for_static_block = (BigInteger::static_block(), true);
//	
//	void BigInteger::static_block() {
//		std::srand(std::time(NULL));
//	}
//
//	// You can change this value for your machine
//	size_v BigInteger::max_size_for_std_mult = 250;
//
//	BigInteger::BigInteger(size_p* value, size_v size, size_v real_size, bool isNegate = false) {
//		this->value = value;
//		this->size = size;
//		this->real_size = real_size;
//		this->isNegate = isNegate;
//	}
//
//	size_v inline get(size_p* val, size_v size, size_v real_size, size_v index) {
//		return index >= 0 && index < size && index < real_size ? val[index] : 0;
//	}
//
//	void BigInteger::_sum(size_p* a, size_v a_size, size_v a_real_size, size_p* b, size_v b_size, size_v b_real_size, size_p** out, size_v* out_size, size_v* out_real_size, bool createNew = true) {
//		
//		size_v min_size;
//		size_v max_size;
//		size_v min_real_size;
//		size_v max_real_size;
//		size_p* min_number;
//		size_p* max_number;
//
//		if (a_size < b_size) {
//			min_real_size = a_real_size;
//			max_real_size = b_real_size;
//			min_size = a_size;
//			max_size = b_size;
//			min_number = a;
//			max_number = b;
//		}
//		else {
//			min_real_size = b_real_size;
//			max_real_size = a_real_size;
//			min_size = b_size;
//			max_size = a_size;
//			min_number = b;
//			max_number = a;
//		}
//
//		size_p* _out;
//
//		if (createNew)
//			_out = new size_p[max_size + 1];
//		else 
//			_out = *out;
//		_out[0] = 0;
//
//		for (size_v i = 0; i < min_size; i++) {
//			_out[i] += get(min_number, min_size, min_real_size, i) + get(max_number, max_size, max_real_size, i);
//			_out[i + 1] = _out[i] / BigInteger::max_size_of_part;
//			_out[i] = _out[i] % BigInteger::max_size_of_part;
//		}
//
//		for (size_v i = min_size; i < max_size; i++) {
//			_out[i] += get(max_number, max_size, max_real_size, i);
//			_out[i + 1] = _out[i] / BigInteger::max_size_of_part;
//			_out[i] = _out[i] % BigInteger::max_size_of_part;
//		}
//
//		*out = _out;
//		*out_real_size = max_size + 1;
//		while (_out[max_size] == 0) max_size--;
//		*out_size = max_size + 1;
//	}
//
//	void BigInteger::_sub(size_p* a, size_v a_size, size_v a_real_size, size_p* b, size_v b_size, size_v b_real_size, size_p** out, size_v* out_size, size_v* out_real_size, bool createNew = true) {
//		size_v min_size;
//		size_v max_size;
//		size_v min_real_size;
//		size_v max_real_size;
//		size_p* min_number;
//		size_p* max_number;
//
//		if (a_size < b_size || (a_size == b_size && a[a_size - 1] < b[b_size - 1])) {
//			min_size = a_size;
//			max_size = b_size;
//			min_real_size = a_real_size;
//			max_real_size = b_real_size;
//			min_number = a;
//			max_number = b;
//		}
//		else {
//			min_size = b_size;
//			max_size = a_size;
//			min_real_size = b_real_size;
//			max_real_size = a_real_size;
//			min_number = b;
//			max_number = a;
//		}
//
//		size_p* _out;
//		if (createNew)
//			_out = new size_p[max_size + 1];
//		else
//			_out = *out;
//		_out[0] = 0;
//
//		for (size_v i = 0; i < max_size; i++) {
//			_out[i] += get(max_number, max_size, max_real_size, i) - get(min_number, min_size, min_real_size, i);
//			_out[i + 1] = 0;
//
//			while (_out[i] < 0) {
//				_out[i + 1] -= 1;
//				_out[i] += BigInteger::max_size_of_part;
//			}
//		}
//
//		if (max_number != a) _out[max_size] = -1;
//
//
//		*out = _out;
//		*out_size = (*out_real_size = max_size + 1) - 1;
//	}
//
//	void BigInteger::_multStandart(size_p* a, size_v a_size, size_v a_real_size, size_p* b, size_v b_size, size_v b_real_size, size_p** out, size_v* out_size, size_v* out_real_size, bool createNew = true) {
//		size_v min_size;
//		size_v max_size;
//		size_v min_real_size;
//		size_v max_real_size;
//		size_p* min_number;
//		size_p* max_number;
//
//		if (a_size < b_size) {
//			min_real_size = a_real_size;
//			max_real_size = b_real_size;
//			min_size = a_size;
//			max_size = b_size;
//			min_number = a;
//			max_number = b;
//		}
//		else {
//			min_real_size = b_real_size;
//			max_real_size = a_real_size;
//			min_size = b_size;
//			max_size = a_size;
//			min_number = b;
//			max_number = a;
//		}
//
//		size_v size = a_size + b_size + 1;
//		size_p* _out;
//		if (createNew)
//			_out = new size_p[size];
//		else
//			_out = *out;
//		
//		memset(_out, 0, sizeof(size_p) * size);
//
//		for (size_v i = 0; i < min_size; i++)
//			for (size_v j = 0; j < max_size; j++) {
//				_out[i + j] += get(min_number, min_size, min_real_size, i) * get(max_number, max_size, max_real_size, j);
//				_out[i + j + 1] += _out[i + j] / BigInteger::max_size_of_part;
//				_out[i + j] = _out[i + j] % BigInteger::max_size_of_part;
//			}
//
//		*out = _out;
//		*out_real_size = size;
//		while (_out[size - 1] == 0 && size > 1) size--;
//		*out_size = size;
//	}
//
//	void BigInteger::_multInMiddle(size_p* a, size_v a_size, size_v a_real_size, size_p* b, size_v b_size, size_v b_real_size, size_p** out, size_v* out_size, size_v* out_real_size, bool createNew = true) {
//		if (a_size < 1 || a_real_size < 1 || b_size < 1 || b_real_size < 1) {
//			(*out_size) = (*out_real_size) = 0;
//			return;
//		}
//
//		size_v max_size = max(a_size, b_size);
//
//		if (max_size <= max_size_for_std_mult)
//			return _multStandart(a, a_size, a_real_size, b, b_size, b_real_size, out, out_size, out_real_size, createNew);
//
//		while (max_size & (max_size - 1)) max_size++;
//		size_v middle = max_size / 2;
//
//		size_p* P1;
//		size_v P1_size;
//		size_v P1_real_size;
//		_multInMiddle(a + middle, middle, min(middle, sizeSub(a_real_size, middle)), b + middle, middle, min(middle, sizeSub(b_real_size, middle)), &P1, &P1_size, &P1_real_size);
//
//		size_p* P2;
//		size_v P2_size;
//		size_v P2_real_size;
//		_multInMiddle(a, middle, min(middle, a_real_size), b, middle, min(middle, b_real_size), &P2, &P2_size, &P2_real_size);
//
//		size_p* Xlr;
//		size_v Xlr_size;
//		size_v Xlr_real_size;
//		_sum(a + middle, middle, min(middle, sizeSub(a_real_size, middle)), a, middle, min(middle, a_real_size), &Xlr, &Xlr_size, &Xlr_real_size);
//
//		size_p* Ylr;
//		size_v Ylr_size;
//		size_v Ylr_real_size;
//		_sum(b + middle, middle, min(middle, sizeSub(b_real_size, middle)), b, middle, min(middle, b_real_size), &Ylr, &Ylr_size, &Ylr_real_size);
//
//		size_p* P3;
//		size_v P3_size;
//		size_v P3_real_size;
//		_multInMiddle(Xlr, Xlr_size, Xlr_real_size, Ylr, Ylr_size, Ylr_real_size, &P3, &P3_size, &P3_real_size);
//
//		(*out_real_size) = ((*out_size) = 2 * max_size) + 1;
//		(*out) = new size_p[(*out_real_size)];
//		(*out)[0] = 0;
//
//		for (size_v i = 0; i < *out_size; i++) {
//			(*out)[i + 1] = 0;
//			(*out)[i] += get(P2, P2_size, P2_real_size, i) + (get(P3, P3_size, P3_real_size, i - middle) - get(P1, P1_size, P1_real_size, i - middle) - get(P2, P2_size, P2_real_size, i - middle)) + get(P1, P1_size, P1_real_size, i - max_size);
//
//			while ((*out)[i] < 0) {
//				(*out)[i + 1] -= 1;
//				(*out)[i] += BigInteger::max_size_of_part;
//			}
//
//			while ((*out)[i] >= BigInteger::max_size_of_part) {
//				(*out)[i + 1] += (*out)[i] / BigInteger::max_size_of_part;
//				(*out)[i] = (*out)[i] % BigInteger::max_size_of_part;
//			}
//			
//		}
//
//		while ((*out)[(*out_size) - 1] == 0) (*out_size)--;
//
//		if (P1_real_size > 0) delete[] P1;
//		if (P2_real_size > 0) delete[] P2;
//		if (P3_real_size > 0) delete[] P3;
//		if (Xlr_real_size > 0) delete[] Xlr;
//		if (Ylr_real_size > 0) delete[] Ylr;
//	}
//
//
//	//------------------Public Section------------\\
//		
//	BigInteger::BigInteger() {
//		this->size = 0;
//		this->real_size = 0;
//		this->value = 0;
//		this->isNegate = false;
//	}
//
//	BigInteger::BigInteger(const BigInteger& b) {
//		this->isNegate = b.isNegate;
//
//		this->real_size = this->size = b.size;
//
//		this->value = new size_p[this->real_size];
//
//		for (size_v i = 0; i < b.size; i++) {
//			this->value[i] = b.value[i];
//		}
//	}
//
//	BigInteger::BigInteger(std::string& str) {
//		if (str.length() < 1) throw _LPL_ERROR_STRING(1);
//
//		int str_index = 0;
//		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;
//
//		size_v size = (str.length() - str_index) / BigInteger::max_length_of_part + ((str.length() - str_index) % BigInteger::max_length_of_part > 0 ? 1 : 0);
//
//		size_p* value = new size_p[size];
//
//		size_v j = 0;
//		size_p number = 0;
//		int8_t number_length = 0;
//		for (int i = 0; i < str.length() - str_index; i++) {
//			size_p tmp = number + (str[str.length() - i - 1] - '0') * pow(10, number_length);
//			if (tmp < BigInteger::max_size_of_part && number_length < BigInteger::max_length_of_part) {
//				number = tmp;
//				number_length++;
//			}
//			else {
//				value[j++] = number;
//				number_length = 0;
//				number = (str[str.length() - i - 1] - '0') * pow(10, number_length++);
//			}
//		}
//
//		if (number > 0) {
//			value[j++] = number;
//		}
//
//		this->value = value;
//		this->size = j;
//		this->real_size = size;
//	}
//
//	BigInteger::BigInteger(const char* str) {
//		int str_length = strlen(str);
//
//		if (str_length < 1) throw _LPL_ERROR_STRING(1);
//
//		int str_index = 0;
//		if (str[0] == '-' || str[0] == '-') this->isNegate = ++str_index;
//
//		size_v size = (str_length - str_index) / BigInteger::max_length_of_part + ((str_length - str_index) % BigInteger::max_length_of_part > 0 ? 1 : 0);
//
//		size_p* value = new size_p[size];
//
//		size_v j = 0;
//		size_p number = 0;
//		int8_t number_length = 0;
//		for (int i = 0; i < str_length - str_index; i++) {
//			size_p tmp = number + (str[str_length - i - 1] - '0') * pow(10, number_length);
//			if (tmp < BigInteger::max_size_of_part && number_length < BigInteger::max_length_of_part) {
//				number = tmp;
//				number_length++;
//			}
//			else {
//				value[j++] = number;
//				number_length = 0;
//				number = (str[str_length - i - 1] - '0') * pow(10, number_length++);
//			}
//		}
//
//		if (number > 0 || j < 1) {
//			value[j++] = number;
//		}
//
//		this->value = value;
//		this->size = j;
//		this->real_size = size;
//	}
//
//	BigInteger::BigInteger(const size_p & value) {
//		this->size = this->real_size = 1;
//		this->value = new size_p[1];
//
//		if (value < 0) {
//			this->isNegate = true;
//			this->value[0] = -value;
//		}else
//			this->value[0] = value;
//		
//	}
//
//	BigInteger::BigInteger(const usize_p & value, bool isNegate) {
//		this->size = this->real_size = 1;
//		this->value = new size_p[1];
//		this->value[0] = value;
//		this->isNegate = isNegate;
//	}
//
//	BigInteger::~BigInteger() {
//		if (this->value != 0) delete[] this->value;
//	}
//
//	BigInteger BigInteger::add(const BigInteger& b, int type) {
//		switch (type) {
//		default:
//			if (this->size < 1 || b.size < 1) return BigInteger();
//
//			size_p* out = 0;
//			size_v out_size = 0;
//			size_v out_real_size = 0;
//			bool isNegate = false;
//
//			if (!this->isNegate && !b.isNegate) {
//				_sum(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//			}
//			else if (!this->isNegate && b.isNegate) {
//				_sub(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				if (out[out_size - 1] > BigInteger::max_size_of_part) {
//					isNegate = true;
//					out_size--;
//				}
//				while (out_size > 1 && out[out_size - 1] == 0) out_size--;
//			}
//			else if (this->isNegate && !b.isNegate) {
//				_sub(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				if (out[out_size - 1] <= BigInteger::max_size_of_part) {
//					isNegate = true;
//					out_size--;
//				}
//				while (out_size > 1 && out[out_size - 1] == 0) out_size--;
//			}
//			else if (this->isNegate && b.isNegate) {
//				_sum(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				isNegate = true;
//			}
//			else return BigInteger();
//
//			return BigInteger(out, out_size, out_real_size, isNegate);
//			break;
//		}
//	} 
//
//	BigInteger BigInteger::sub(const BigInteger& b, int type) {
//		switch (type) {
//		default:
//			if (this->size < 1 || b.size < 1) return BigInteger();
//
//			size_p* out = 0;
//			size_v out_size = 0;
//			size_v out_real_size = 0;
//			bool isNegate = false;
//			if (!this->isNegate && !b.isNegate) {
//				_sub(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				if (out[out_real_size - 1] == -1) {
//					isNegate = true;
//					out_size--;
//				}
//				while (out_size > 1 && out[out_size - 1] == 0) out_size--;
//			}
//			else if (!this->isNegate && b.isNegate) {
//				_sum(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//			}
//			else if (this->isNegate && !b.isNegate) {
//				_sum(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				isNegate = true;
//			}
//			else if (this->isNegate && b.isNegate) {
//				_sub(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//				if (out[out_real_size - 1] == -1) {
//					isNegate = true;
//					out_size--;
//				}
//				while (out_size > 1 && out[out_size - 1] == 0) out_size--;
//			}
//			else 
//				return BigInteger();
//
//			return BigInteger(out, out_size, out_real_size, isNegate);
//			break;
//		}
//	}
//
//	BigInteger BigInteger::mult(const BigInteger& b, int type) {
//		if (this->size < 1 || b.size < 1) return BigInteger();
//
//		size_p* out = 0;
//		size_v out_size = 0;
//		size_v out_real_size = 0;
//		switch (type) {
//		case KARATSUBA_MULT:
//			_multInMiddle(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//			break;
//		default:
//			_multStandart(this->value, this->size, this->size, b.value, b.size, b.size, &out, &out_size, &out_real_size);
//			break;
//		}
//
//		return BigInteger(out, out_size, out_real_size, this->isNegate != b.isNegate);
//	}
//
//	BigInteger BigInteger::operator + (const BigInteger& b) {
//		return add(b, STD_SUM);
//	}
//
//	BigInteger BigInteger::operator - (const BigInteger& b) {
//		return sub(b, STD_SUB);
//	}
//
//	BigInteger BigInteger::operator * (const BigInteger& b) {
//		return mult(b, KARATSUBA_MULT);
//	}
//
//	BigInteger& BigInteger::operator = (const BigInteger& b) {
//		if (this->real_size < (this->size = b.size)) {
//			if (this->value != 0) delete[] value;
//
//			this->real_size = this->size;
//			value = new size_p[this->real_size];
//		}
//
//		this->isNegate = b.isNegate;
//
//		for (size_v i = 0; i < this->size; i++) {
//			this->value[i] = b.value[i];
//		}
//
//		return *this;
//	}
//
//	std::string BigInteger::toString() {
//
//		std::string ret = std::string("");
//		if (this->size <= 0) ret.append("NaN");
//		else {
//
//			if (this->isNegate && (this->size > 1 || this->value[0] != 0)) ret.append("-");
//
//			for (size_v i = 0; i < this->size; i++) {
//				std::string tmp = std::to_string(this->value[this->size - i - 1]);
//				while (tmp.length() < BigInteger::max_length_of_part && i != 0) {
//					tmp = "0" + tmp;
//				}
//				ret.append(tmp);
//			}
//		}
//		return ret;
//	}
//
//	bool BigInteger::operator < (const BigInteger& b) {
//		if (this->isNegate != b.isNegate) return this->isNegate && !b.isNegate;
//		if (this->size != b.size) return this->isNegate && b.isNegate && this->size > b.size || !this->isNegate && !b.isNegate && this->size < b.size;
//
//		for (size_v i = 0; i < this->size; i++) {
//			if (this->value[i] > b.value[i]) return this->isNegate;
//		}
//
//		return !this->isNegate;
//	}
//
//	bool BigInteger::operator > (const BigInteger& b) {
//		if (this->isNegate != b.isNegate) return !this->isNegate && b.isNegate;
//		if (this->size != b.size) return this->isNegate && b.isNegate && this->size < b.size || !this->isNegate && !b.isNegate && this->size > b.size;
//
//		for (size_v i = 0; i < this->size; i++) {
//			if (this->value[i] < b.value[i]) return this->isNegate;
//		}
//
//		return !this->isNegate;
//	}
//
//	bool BigInteger::operator <= (const BigInteger& b) {
//		return !((*this) > b);
//	}
//
//	bool BigInteger::operator >= (const BigInteger& b) {
//		return !((*this) < b);
//	}
//
//	bool BigInteger::operator == (const BigInteger& b) {
//		if (this->isNegate != b.isNegate || this->size != b.size) return false;
//
//		for (size_v i = 0; i < this->size; i++) {
//			if (this->value[i] != b.value[i]) return false;
//		}
//
//		return true;
//	}
//
//	bool BigInteger::operator != (const BigInteger& b) {
//		return !((*this) == b);
//	}
//
//	bool BigInteger::isNegative() {
//		return this->isNegate;
//	}
//
//	bool BigInteger::isPositive() {
//		return !this->isNegate;
//	}
//
//	bool BigInteger::isNaN() {
//		return this->size == 0;
//	}
//
//	BigInteger BigInteger::random(size_v length = 20){
//		std::stringstream ret;
//		size_v number_length = 0;
//
//		while (number_length < length) {
//			std::string tmp = std::to_string(rand());
//			number_length += tmp.length();
//			ret << tmp;
//		}
//		std::string _ret = ret.str().substr(0, length);
//		return BigInteger(_ret);
//	}
//
//	void BigInteger::setMaxSizeForSTDMult(size_v size) {
//		if (size > 0) BigInteger::max_size_for_std_mult = size;
//	}
//};