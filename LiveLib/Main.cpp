/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/

#include <iostream>
#include <chrono>
#include "BigInteger.h"
#include <fstream>
using namespace livelib;
using namespace std;

int main() {
	/*BigInteger a = BigInteger::random(4000000);
	BigInteger b = BigInteger::random(4000000);

	double sum = 0;
	int i = 0;
	int count_iter = 1000;
	int count_output = 10;

	for (; i < count_iter; i++) {
		auto s = getTime();

		BigInteger c = a * b;

		auto e = getTime();

		sum += getTimeM(s, e);

		if (i % (count_iter / count_output) == 0 && i != 0)
			cout << "Middle time for iteration: " << i << " = " << sum / i << " ms\n";
	}*/

	

	//cout << getTimeN(s, e) << "\n";
	//cout << c.toString() << "\n";


	BigInteger a0 = BigInteger::random(3200);
	BigInteger b0 = BigInteger::random(3200);

	auto s0 = getTime();
	//BigInteger c0 = a0.mult(b0, STD_MULT);
	auto e0 = getTime();

	auto s1 = getTime();
	BigInteger c1 = a0.mult(b0, KABYC_MULT);
	auto e1 = getTime();

	//cout << (c0 == c1) << '\n';

	cout << "Time #0: " << getTimeM(s0, e0) << '\n';
	cout << "Time #1: " << getTimeM(s1, e1) << '\n';
	system("pause");
	return 0;
}