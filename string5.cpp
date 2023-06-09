#ifdef _MSC_VER
// MSC ne adjon figyelmeztető üzenetet a C sztringkezelő függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringműveletekhez
#include <cstddef>

#include "string5.h"

size_t String::size() const { return len; }

const char* String::c_str() const { return pData; }


/// Konstruktorok: egy char karakterből (createString)
///                egy nullával lezárt char sorozatból (createString)
/// 
String::String() :len(0) {
    pData = new char[1];
    pData[0] = '\0';
}

String::String(const char c) {
    len = 1;
    pData = new char[len + 1];
    pData[0] = c;
    pData[1] = '\0';
}

String::String(const char* string) {
    len = strlen(string);
    pData = new char[len + 1];
    strcpy(pData, string);
}

/// Másoló konstruktor: String-ből készít (createString)
String::String(const String& s) :len(s.len){
    pData = new char[len + 1];
    strcpy(pData, s.pData);
}

//ctor int-ből
String::String(const int i)
{
    len = 0;
    int temp = i;
    while (temp != 0) {
        temp /= 10;
        len++;
    }

    pData = new char[len + 1];
    pData[len] = '\0';

    int szam = i;

    for (int j = len - 1; j >= 0; j--) {
        pData[j] = '0' + (szam % 10);
        szam /= 10;
    }
}

/// Destruktor (disposeString)
String::~String() {
    delete[] pData;
}

/// operator=
String& String::operator=(const String& s) {
    if (this == &s) {
        return *this;
    }
    len = s.len;
    delete[] pData;
    pData = new char[len + 1];
    strcpy(pData, s.pData);
    return *this;
}


/// [] operátorok: egy megadott indexű elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
char& String::operator[](size_t idx) const {
    if (idx >= len) throw "PRUHJB";
    return pData[idx];
}

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
String operator+(const String& s, const char c) {
    size_t string_size = s.size();
    char* temp = new char[string_size + 2];
    strcpy(temp, s.c_str());
    temp[string_size] = c;
    temp[string_size + 1] = '\0';
    String res = String(temp);
    delete[] temp;
    return res;
}

///                 String-hez String-et ad (addString)
String operator+(const String& a, const String& b) {
    size_t len = a.size() + b.size();
    char* temp = new char[len + 1];
    strcpy(temp, a.c_str());
    strcat(temp, b.c_str());
    String res = String(temp);
    delete[] temp;
    return res;
}

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << s.c_str();
}

/// >> operátor, ami beolvas az istream-ről egy szót
std::istream& operator>>(std::istream& is, String& s) {
    is.unsetf(std::istream::skipws);
    char c;
    is >> c; //inicializálom
    while (isspace(c)) { is >> c; } //eldobja a kezdeti wspaceket
    s = String(c); //inicializálom a Stringet
    is >> c; //első karakter már nem kell
    while (!isspace(c) && !is.eof()) {
        s = s + c; //Hozzáadok minden karaktert (amíg az nem wspace)
        is >> c;
    }
    return is;
}

void String::getline(std::istream& is) {
    char ch;
    *this = String("");
    while (is.get(ch)) {
        if (ch == '\n' || ch == '\0') break;
        else {
            *this = *this + ch;
        }
    }
}