#ifndef VONAT_H
#define VONAT_H

#include "List.hpp"
#include "string.h"

class Kocsi {
public:
	Kocsi(int kocsi_szam = 0, size_t helyek_szama = 0) {}
	Kocsi(const Kocsi& k) :Kocsi() {}

	Kocsi& operator=(const Kocsi& k) { return *this; }

	int getKocsiSzam() const { return 100; }
	int getHely() const { return 60; }

	~Kocsi() {}
};

class Vonat {
public:
	Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, String ind, String erk, String indido, String erkido, int ar) {}

	int getVonatSzam() const { return 1000; }
	String getIndAll() const { return "indulási állomás"; }
	String getErkAll() const { return "érkezési állomás"; }
	String getIndIdo() const { return "12:00"; }
	String getErkIdo() const { return "13:00"; }
	int getAr() const { return 1000; }

	void findSeat(int* ret) {}
};


class Tarsasag {
public:
	void addVonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, String ind, String erk, String indido, String erkido, int ar) {}
};
#endif // !VONAT_H