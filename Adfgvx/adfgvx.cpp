#include "adfgvx.h"

using namespace std;

std::string Adfgvx::randomiseAdfgvxTab(){

	static int i = 0;
	if(i == 0){
		srand(time(nullptr));
		i++;
	}
	std::string P = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string key;
	int index = rand()%26;
	for(int i= 0; i< 6; i++){
		for(int j=0; j< 6; j++){
			while(P[index] == ' '){
				index = rand()%36;
			}
			Table[i][j] = P[index];
			key.push_back(P[index]);
			P[index] = ' ';
		}
	}
	return key;
}
std::string Adfgvx::encrypt(std::string message){

	std::string cryptagramme;
	for(int i=0, j= message.size(); i< j; i++){
		if(message[i] == ' '){
			cryptagramme.push_back(' ');
			continue;
		}
		auto pair = getKey(message[i]);
		cryptagramme.push_back(pair.first);
		cryptagramme.push_back(pair.second);
	}
	return cryptagramme;

}
std::string Adfgvx::deCrypt(std::string cryptogramme){
	std::string message;
	for(int i=0, j= cryptogramme.size()+1; i< j; i++){
		if(cryptogramme[i] == ' '){
			message.push_back(' ');
			continue;
		}
		char c = getValue(cryptogramme[i], cryptogramme[i+1]);
		message.push_back(c);
		i++;
	}
	return message;
}

std::pair<char, char> Adfgvx::getKey(char c){
	c= toupper(c);
	auto pair = std::pair<char, char>(' ', ' ');
	std::string ADFGVX = "ADFGVX";
	for(int i=0; i< 6; i++){
		for(int j=0; j< 6; j++){
			if(Table[i][j] == c){
				pair.first = ADFGVX[i];
				pair.second = ADFGVX[j];
				return pair;
			}
		}
	}
	return pair;
}

char Adfgvx::getValue(char row, char col){
	std::string ADFGVX = "ADFGVX";
	row = toupper(row);
	col = toupper(col);
	for(int i=0; i< 6; i++){
		if(ADFGVX[i] == row){
			for(int j=0; j< 6; j++){
				if(ADFGVX[j] == col){
					return Table[i][j];
				}
			}
		}
	}
	return ' ';
}


void Adfgvx::printTable(){
	std::cout<<"Key: \n";
	std::string key = "\tA D F G V X\n";
	std::string ADFGVX = "ADFGVX";
	for(int i=0; i< 6; i++){
		key+="\n "; key.push_back(ADFGVX[i]);
		key+= "\t";
		for(int j=0; j< 6; j++){
			key.push_back(Table[i][j]);
			key+= " ";
		}
	}
	std::cout<<key<<std::endl;
}