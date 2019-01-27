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
	BigInteger a = BigInteger::random(40000000);
	BigInteger b = BigInteger::random(40000000);

	auto s = getTime();

	BigInteger c = a + b;

	auto e = getTime();

	cout << getTimeM(s, e) << "\n";
	//cout << c.toString() << "\n";

	system("pause");
	return 0;
}