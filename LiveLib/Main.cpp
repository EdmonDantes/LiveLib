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

	string i = "11";
	i = i + "225" + "09";
	BigInteger a = BigInteger::random(40000000);
	BigInteger b = BigInteger::random(40000000);

	auto start = chrono::steady_clock::now();

	BigInteger c = a + b;

	auto end = chrono::steady_clock::now();

	cout << chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\n";

	system("pause");
	return 0;
}