/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/

#include <iostream>
#include <chrono>
#include "BigInteger.h"
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


	BigInteger a0 = BigInteger("99999999999999999999");
	BigInteger b0 = BigInteger("-99999999999999999999");

	int index = 0;
	while (index++ < 100)
		BigInteger test = a0 + b0;



	auto s = getTime();
	BigInteger c0 = a0 * b0;

	auto e = getTime();

	cout << c0.toString() << "\n" << getTimeN(s, e) << "\n";
	system("pause");
	return 0;
}