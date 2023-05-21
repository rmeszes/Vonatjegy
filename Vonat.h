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

	~Kocsi() { delete[] helyek; }
};

/// <summary>
/// A két adat összekötésére szolgál
/// Minden vonat az Állomás saját példányait tárolja, ezért köthetõ hozzá az idõ.
/// </summary>
struct Allomas { 
	String nev; 
	String ido;
	Allomas(const char* nev, const char* ido) :nev(nev), ido(ido) {}
	Allomas(const String& nev, const String& ido) :nev(nev), ido(ido) {}
	Allomas() :nev(""), ido("") {}
};

class Vonat {
	int vonat_szam;
	size_t kocsik_szama;
	int ar;
	List<Allomas> allomasok;
	List<Kocsi> kocsik;
public:
	Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, int ar, List<Allomas>& allomasok);

	int getVonatSzam() const { return vonat_szam; }
	int getAr() const { return ar; }

	void findSeat(int* ret);
};
#endif // !VONAT_H