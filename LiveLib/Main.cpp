/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <random>
#include "NumberSystemConverter.h"
using namespace livelib;
using namespace numsysconverter;
using namespace std;

int main() {

	srand(time(NULL));

	ConvertConfig conf = ConvertConfig(10, 2);
	std::string number = "";

	for (int i = 0; i < 50; i++) {
		number += (char) ((rand() % 9) + '0');
	}

	auto s = getTime();
	BitStream* bs = convertTo(number, conf);
	auto e = getTime();

	cout << getTimeMilli(s, e) << "\n\n\n\n";

	cout << number << "\n\n";
	cout << toString(bs, conf) << "\n\n";

	system("pause");
}