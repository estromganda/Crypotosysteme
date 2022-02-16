#include "cryptosystemFlot.h"

CryptosystemFlot::Ascii::Ascii(char const& c): m_character(c), m_binaire(""){
    int dividend = c;
    int i=0;
    while(dividend> 0){
        m_binaire = (dividend%2 == 0 ? "0" : "1") + m_binaire;
        dividend = dividend/2;
        if(i == 8) break;
    }
    while(m_binaire.size()< 8)
        m_binaire = "0"+m_binaire;
}

CryptosystemFlot::Ascii::Ascii(std::string const& binaire): m_binaire(binaire){
    int character= 0;
    for(int i=0, ii= binaire.size(); i< ii; i++){
        m_binaire[i] = binaire[i];
        if(binaire[i] == '1')
            character+= pow(2, 7-i);
    }
    m_character = character;
}

char CryptosystemFlot::Ascii::character(){
    return m_character;
}

std::string CryptosystemFlot::Ascii::xOr(const Ascii &ascii){
    std::string str("");
    for(int i=0; i<8; i++){
        str+= (m_binaire[i] != ascii[i] ? "1" : "0");
    }

    return str;
}

std::string CryptosystemFlot::Ascii::toBinary(){
    return m_binaire;
}

CryptosystemFlot::Ascii::~Ascii(){}

void CryptosystemFlot::Ascii::operator=(char const& c){
    m_character = c;
}
int CryptosystemFlot::Ascii::operator[](int i) const{
    return m_binaire[i];
}

std::pair<std::string, std::string> CryptosystemFlot::encrypt(const std::string &message){
    std::string cryptogramm(message);
    std::string key(message);

    //Generation de clé de façon aleatoir
    bool static isRand = false;
    if(!isRand)
        srand(time(nullptr));
    isRand = true;
    for(int i=0, ii= key.size(); i< ii; i++){
        key[i] = char(rand() % 256);
        while(!isprint(key[i]))
            key[i] = char(rand() % 256);
    }
    //Cryptage
    for(int i=0, ii= message.size(); i< ii; i++){
        //if(message[i] == ' ') continue;
        cryptogramm[i] = Ascii(Ascii(message[i]).xOr(key[i])).character();
        while(!isprint(cryptogramm[i])){
            key[i] = random()%256;
            while(!isprint(key[i]))
                key[i] = char(rand() % 256);
            cryptogramm[i] = Ascii(Ascii(message[i]).xOr(key[i])).character();
        }
    }
    return std::pair<std::string, std::string>(cryptogramm, key);
}

std::string CryptosystemFlot::deccrypt(const std::string &cryptogramme, const std::string &key){

    std::string message(cryptogramme);
    for(int i=0, ii= cryptogramme.size(), iii= key.size(); i< ii || i< iii; i++){
        //if(message[i] == ' ') continue;
        message[i] = Ascii(Ascii(message[i]).xOr(key[i])).character();
    }
    return message;
}

std::string CryptosystemFlot::strAsBinairy(const std::string &txt)
{
    std::string str("");
    for(int i=0, ii= txt.size(); i< ii; i++){
        //str+= txt[i] == ' ' ? " " : Ascii(txt[i]).toBinary();
        str+= Ascii(txt[i]).toBinary()+" ";
    }
    return str;
}
