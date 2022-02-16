#ifndef CRYPTOSYSTEMFLOT_H
#define CRYPTOSYSTEMFLOT_H

#include <iostream>
#include <cmath>


namespace CryptosystemFlot{
    class Ascii
    {
    public:
        Ascii(const char &c);
        Ascii(const std::string &binaire);
        char character();
        std::string xOr(Ascii const& ascii);
        std::string toBinary();
        ~Ascii();
        void operator=(char const& c);
        int operator [](int i) const;

        private:
            char m_character;
            std::string m_binaire;
    };

    std::pair<std::string, std::string> encrypt(std::string const& message);
    std::string deccrypt(std::string const& cryptogramme, std::string const& key);
    std::string strAsBinairy(std::string const& txt);
};


#endif // CRYPTOSYSTEMFLOT_H
