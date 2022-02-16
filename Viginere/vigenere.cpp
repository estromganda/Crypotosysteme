#include "vigenere.h"

using namespace std;

string Vigenere::getCode(string const& msg, string const& key){
	string code = msg;
	int j= 0;
	for(int i=0, ii= code.size(); i< ii; i++){
		if(code[i] != ' ')
			code[i] = key[(j++) % key.size()];
	}
	return code;
}

void Vigenere::initP(){
	static bool isInit = false;
	if(isInit) return;
	viginereTab[0][0] = ' ';
	for(int i=1; i< 27; i++){
		viginereTab[0][i] = P[i-1];
		viginereTab[i][0] = P[i-1];
	}
	
	for(int i=1; i< 27; i++){
		for(int j= 1; j< 27; j++){
			char c = viginereTab[i][0]+j-1;
			c = c> 'Z' ? c - 'Z' + 'A' -1 :  c;
			viginereTab[i][j] = c;
		}
	}
	isInit= true;
}

char Vigenere::getXy(char cx, char cy){
	initP(); 
	cx = toupper(cx);
	cy = toupper(cy);
	for(int x=1; x<27; x++){
		if(viginereTab[0][x] == cx){
			for(int y=0; y< 27; y++){
				if(viginereTab[y][0] == cy)
					return viginereTab[x][y];
			}
		}
	}
	return char(' ');
}

int Vigenere::getIndexOf(char c){
    for(int i=0; i< 26; i++){
        if(c == P[i])
            return i;
    }
    return -1;
}

string Vigenere::encrypt(string const& message, string const& key){
	initP();
    string code = getCode(message, key);
	string texteCrypte= code;
    for(int i=0, ii= code.size(); i< ii; i++){
        texteCrypte[i]= std::islower(message[i]) ? std::tolower(getXy(message[i], code[i])) : std::toupper(getXy(message[i], code[i]));
	}
	return texteCrypte;
}

std::string Vigenere::decrypt(std::string const& texteCrypte, const string &key){
    initP();
    std::string code = getCode(texteCrypte, key);
    std::string texteClaire= texteCrypte;
    for(int i= 0, ii = code.size(); i< ii; i++){
        char c= code[i], p= texteCrypte[i];
        c= std::toupper(c); p= std::toupper(p);
		for(int j= 1;j< 27; j++){
			if(viginereTab[1][j] == c){
                for(int k=1; k< 27; k++){
                    if(viginereTab[k][j] == p){
						texteClaire[i] = viginereTab[k][1];
						break;
					}
				}
				break;
			}
		}
	}
	return texteClaire;
}

void Vigenere::printViginereTab(){
	initP();
	for(int i=0; i< 27; i++){
		for(int j=0; j< 27; j++){
			cout<<viginereTab[i][j];
		}
		cout<<endl;
	}
}
