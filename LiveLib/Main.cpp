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

	ConvertConfig conf = ConvertConfig(2, 64);
	std::string number = "";


	for (int j = 1000; j < 20000; j += 250) {

		number = "";

		for (int i = 0; i < j; i++) {
			number += (char) ((rand() % 2) + '0');
		}

		auto s = getTime();
		BitStream* bs = convertTo(number, conf);
		auto e = getTime();

		cout << j << " = " << getTimeMilli(s, e) << "\n";
	}

	//cout << number << "\n\n";
	//cout << toString(bs, conf) << "\n\n";

	system("pause");
}