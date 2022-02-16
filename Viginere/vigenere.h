#ifndef VIGENERE_H
#define VIGENERE_H

#include <iostream>
#include <string>

namespace Vigenere{
	static std::string P="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static char viginereTab[27][27];	
    std::string getCode(std::string const& msg, std::string const& key);
	void initP();
	char getXy(char cx, char cy);
    int getIndexOf(char c);
    std::string encrypt(std::string const& phrase, std::string const& key);
    std::string decrypt(const std::string &texteCrypte, std::string const& key);
	void printViginereTab();
}


#endif
