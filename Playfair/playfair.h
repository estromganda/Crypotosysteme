#include <iostream>
#include <string>

namespace Playfair{

	void setPassword(char tab[5][5], std::string key);
	std::string encrypt(std::string const& message, char tab[5][5]);
	std::string deCrypt(std::string const& cryptogram, char tab[5][5]);
	std::pair<char, char> getKey(char tab[5][5], char c1, char c2);
	std::pair<char, char> getValue(char tab[5][5], char c1, char c2);
	void printDefaultTable();

	static char Table[5][5]= {
		{'E', 'X', 'M', 'P', 'L'},
		{'A', 'Y', 'F', 'I', 'R'},
		{'B', 'C', 'D', 'G', 'H'},
		{'J', 'K', 'N', 'O', 'Q'},
		{'S', 'T', 'U', 'V', 'Z'}
	};
};