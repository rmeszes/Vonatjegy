#ifndef VONAT_H
#define VONAT_H

#include "memtrace.h"
#include "List.hpp"
#include "string.h"
#include "SmartPtr.hpp"

class Kocsi {
	int kocsi_szam;
	bool* helyek;
	size_t helyek_szama;
public:
	Kocsi(int kocsi_szam, size_t helyek_szama);
	Kocsi(const Kocsi& k);

	Kocsi& operator=(const Kocsi& k);

	int getKocsiSzam() const { return kocsi_szam; }
	int getHely() const;

	~Kocsi() { 
		if (helyek_szama != 0) {
			delete[] helyek;
		}
	}
};

/// <summary>
/// A k�t adat �sszek�t�s�re szolg�l
/// Minden vonat az �llom�s saj�t p�ld�nyait t�rolja, ez�rt k�thet� hozz� az id�.
/// </summary>
struct Allomas { 
	String nev; 
	String ido;
	Allomas(const char* nev, const char* ido) :nev(nev), ido(ido) {}
	Allomas(const String& nev = String(""), const String& ido = String("")) :nev(nev), ido(ido) {}
	Allomas(const Allomas& a) :nev(a.nev), ido(a.ido) {}
};

class Vonat {
	int vonat_szam;
	size_t kocsik_szama;
	double ar;
	List<Allomas> allomasok;
	List<Kocsi> kocsik;
public:
	Vonat(int vonat_szam = 0, size_t kocsik_szama = 0, size_t helyek_szama = 0, double ar = 0, List<Allomas>& allomasok = List<Allomas>());

	int getVonatSzam() const { return vonat_szam; }
	int getAr() const { return ar; }

	void findSeat(int* ret);
};
#endif // !VONAT_H