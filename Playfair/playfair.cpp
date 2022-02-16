#include "playfair.h"

void Playfair::setPassword(char tab[5][5], std::string key){
    for(int i=0, ii = key.size(); i< ii; i++){
        for(int j=i+1, jj = key.size(); j< jj; j++){
			if(key[j] == key[i]){
				key.erase(j, 1);
			}
            jj = key.size();
		}
	}
    std::string P = "ABCDEFGHJKLMNOPQRSTUVWXYZ";
	for(int i=0; i< 25; i++){
		bool found = false;
		for(int j=0, jj = key.size(); j< jj; j++){
			if(key[j] == P[i]){
				found = true;
				break;
			}
		}
		if(!found)
			key.push_back(P[i]);
	}
	for(int i=0, ii=0; i< 5; i++){
		for(int j=0; j< 5; j++)
			tab[i][j] = key[ii++];
	}

}

std::string Playfair::encrypt(std::string const& message, char tab[5][5]){
	
	std::string cryptogram = message;
	for(int i = 0, ii= message.size(); i< ii; i++){
		if(message[i] == ' ') 
			continue;
		for(int j= i+1, jj= message.size(); j< jj; j++){
			if(message[j] == ' ') 
				continue;
			auto pair = getKey(tab, message[i], message[j]);
			cryptogram[i] = pair.first;
			cryptogram[j] = pair.second;
			i=j;
			break;
		}
	}
	return cryptogram;
}
std::string Playfair::deCrypt(std::string const& cryptogram, char tab[5][5]){
	
	std::string message = cryptogram;
	for(int i = 0, ii= cryptogram.size(); i< ii; i++){
		if(cryptogram[i] == ' ') continue;
		for(int j= i+1, jj= cryptogram.size(); j< jj; j++){
			if(cryptogram[j] == ' ') 
				continue;
			auto pair = getValue(tab, cryptogram[i], cryptogram[j]);
			message[i] = pair.first;
			message[j] = pair.second;
			i=j;
			break;
		}
	}
	return message;
}

std::pair<char, char> Playfair::getKey(char tab[5][5], char c1, char c2){

    if(toupper(c1) == 'I') c1= 'J';
    if(toupper(c2) == 'I') c2= 'J';

    std::pair<char, char> pair(c1, c1);
	c1 = toupper(c1); c2 = toupper(c2);
	int xC1(-1), yC1(-1), xC2(-1), yC2(-1);
	for(int i=0; i< 5; i++){
		for (int j = 0; j < 5; j++){
			if(toupper(tab[i][j]) == c1){
				xC1 = i; yC1 = j;
			}
			if(toupper(tab[i][j]) == c2){
				xC2 = i; yC2 = j;
			}
		}
	}
	if(xC1 !=-1 && yC1 != -1 && xC2 != -1 && yC2 != -1){
		if(xC1 == xC2){
			pair.first  = tab[xC1][(yC1 + 1) % 5];
			pair.second = tab[xC2][(yC2 + 1) % 5];
		}else if(yC1 == yC2){
			pair.first = tab[(xC1 + 1) % 5][yC1];
			pair.second = tab[(xC2 + 1) % 5][yC2];
		}else{
			pair.first = tab[xC1][yC2];
			pair.second = tab[xC2][yC1];
		}
	}
	return pair;
}

std::pair<char, char> Playfair::getValue(char tab[5][5], char c1, char c2){

    if(toupper(c1) == 'I') c1= 'J';
    if(toupper(c2) == 'I') c2= 'J';

	std::pair<char, char> pair(c1, c1);
	int xC1(-1), yC1(-1), xC2(-1), yC2(-1);
	for(int i=0; i< 5; i++){
		for (int j = 0; j < 5; j++){
			if(tab[i][j] == c1){
				xC1 = i; yC1 = j;
			}
			if(tab[i][j] == c2){
				xC2 = i; yC2 = j;
			}
		}
	}
	if(xC1 !=-1 && yC1 != -1 && xC2 != -1 && yC2 != -1){
		if(xC1 == xC2){
			pair.first = tab[xC1][(yC1 - 1 + 5) % 5];
			pair.second = tab[xC1][(yC2 - 1 + 5) % 5];
		}else if(yC1 == yC2){
			pair.first = tab[(xC1 - 1 + 5) % 5][yC1];
			pair.second = tab[(xC2 - 1 + 5) % 5][yC1];
		}else{
			pair.first = tab[xC1][yC2];
			pair.second = tab[xC2][yC1];
		}
	}
	return pair;
}



void Playfair::printDefaultTable(){
	for(int i=0; i< 5; i++){
		std::cout<<"\t\t";
		for(int j=0; j< 5; j++){
			std::cout<<Table[i][j]<<"    ";
		}
		std::cout<<std::endl;
	}
}

