#ifndef VONAT_H
#define VONAT_H

#include "memtrace.h"
#include "List.hpp"
#include "string.h"

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
/// A két adat összekötésére szolgál
/// Minden vonat az Állomás saját példányait tárolja, ezért köthető hozzá az idő.
/// </summary>
struct Allomas { 
	String nev; 
	String ido;
	Allomas(const char* nev, const char* ido) :nev(nev), ido(ido) {}
	explicit Allomas(const String& nev = String(""), const String& ido = String("")) :nev(nev), ido(ido) {}
	Allomas(const Allomas& a) :nev(a.nev), ido(a.ido) {}
};

class Vonat {
	int vonat_szam;
	size_t kocsik_szama;
	double ar;
	List<Allomas> allomasok;
	List<Kocsi> kocsik;
public:
	explicit Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, double ar, List<Allomas>& allomasok);

	Vonat(const Vonat& original);

	int getVonatSzam() const { return vonat_szam; }
	int getAr() const { return ar; }

	String& induloAll()  { return allomasok.front().nev; }
	String& vegallomas() { return allomasok.back().nev; }

	String& indIdo() { return allomasok.front().ido; }
	String& erkIdo() { return allomasok.back().ido; }

	List<Allomas>& getAllomasok() { return allomasok; }

	void findSeat(int* ret);
};
#endif // !VONAT_H