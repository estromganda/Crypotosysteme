#ifndef ADFGVX_H
#define ADFGVX_H

#include <iostream>
#include <string>

namespace Adfgvx{

	std::string randomiseAdfgvxTab();
	std::string encrypt(std::string message);
	std::string deCrypt(std::string cryptagramme);
	std::pair<char, char> getKey(char c);
	char getValue(char row, char col);
	void printTable();


    static char Table[6][6]{
		{'Q', 'Y', 'A', 'L', 'S', 'E'},
		{'Z', 'X', 'R', 'C', 'H', '0'},
		{'F', 'O', '4', 'M', '8', '7'},
		{'3', 'I', 'T', 'G', 'U', 'K'},
		{'P', 'D', '6', '2', 'N', 'V'},
		{'1', '5', 'J', '9', 'W', 'B'}
	};
}

#endif
