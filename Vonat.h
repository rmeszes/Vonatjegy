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

struct Allomas {
	String nev;
	String ido;
};

class Vonat {
	int vonat_szam;
	size_t kocsik_szama;
	List<Allomas> allomasok;
	int ar;
	List<Kocsi> kocsik;
public:
	Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, String ind, String erk, String indido, String erkido, int ar);

	int getVonatSzam() const { return vonat_szam; }
	String getIndAll() const { return ind; }
	String getErkAll() const { return erk; }
	String getIndIdo() const { return indido; }
	String getErkIdo() const { return erkido; }
	int getAr() const { return ar; }

	void findSeat(int* ret);
};
#endif // !VONAT_H