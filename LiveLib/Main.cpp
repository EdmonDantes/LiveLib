/*
Copyright © 2019 Ilya Loginov. All rights reserved.
Please email dantes2104@gmail.com if you would like permission to do something with the contents of this repository
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <random>
#include <fstream>
#include "convert_util.h"
#include "NumberSystemConverter.h"
using namespace livelib;
using namespace numsysconverter;
using namespace std;

static const char csvChar = ';';

int main() {

	srand(time(NULL));

	uint8* ns = new uint8[4]{ 2,10,16,32};

	ofstream file("output.txt");

	ofstream numberFile("outputNumbers.txt");

	for (int z = 0; z < 4; z++) {

		numberFile << "From" << csvChar << (int) ns[z] << "\n"
			<< "Length of original number" << csvChar << "Length of convert number" << csvChar << "original number" << csvChar << "convert number\n\n";

		file << "From" << csvChar << (int) ns[z] << "\n\nlength of number" << csvChar << "time\n";

		NumberSystem from = NumberSystem(ns[z]);
		NumberSystem to = NumberSystem(64);

		ConvertConfig conf = ConvertConfig(from, to);
		std::string number = "";


		for (int j = 1000; j <= 20000; j += 250) {

			number = "";

			for (int i = 0; i < j; i++) {
				number += convert_util::UIntToChar(rand() % from.numberSystem, from.numberSystem);
			}

			auto s = getTime();
			BitStream* bs = convertTo(number, conf);
			auto e = getTime();

			file << j << csvChar << getTimeNano(s, e) << "\n";

			numberFile << j << csvChar << bs->getCountOfBits() / sizeof(uintmax) << csvChar << number << csvChar << toString(bs, to) << '\n';

			delete bs;

			cout << "Number System = " << (int)ns[z] << "; Length = " << j << '\n';
		}
		numberFile << "\n\n";

		file << "\n\n";

	}

	file.flush();
	file.close();

	numberFile.flush();
	numberFile.close();

	system("pause");
}