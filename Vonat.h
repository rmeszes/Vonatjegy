#ifndef VONAT_H
#define VONAT_H

#include "memtrace.h"
#include "List.hpp"
#include "string5.h"


/// <summary>
/// Egy vonat 1 kocsija. Tárolja a saját számát, ami megjelenik a jegyen és a rajta található helyek foglaltságát.
/// </summary>
class Kocsi {
	int kocsi_szam;
	bool* helyek;
	size_t helyek_szama;
public:
	Kocsi(int kocsi_szam, size_t helyek_szama);
	Kocsi(const Kocsi& k);

	Kocsi& operator=(const Kocsi& k);

	int getKocsiSzam() const { return kocsi_szam; }

	/// <summary>
	/// A kocsin hely lefoglalásáért felel.
	/// </summary>
	/// <returns>A lefoglalt hely száma. 0 ha nincs.</returns>
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

/// <summary>
/// 1 Vonat, tárolja saját azonosítóját, hány kocsija van, mennyi az alapára / állomás, a megállóit, és kocsijait.
/// </summary>
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

	/// <summary>
	/// Egy hely lefoglalására szolgál
	/// </summary>
	/// <param name="ret">Ennek egy legalább 2 méretű int tömbnek kell legyen, a [0]. helyen lesz a kocsi száma,
	/// a [1]. helyen pedig a lefoglalt hely száma jelenik meg.
	/// mindkettő 0, ha a vonaton már minden hely foglalt.</param>
	void findSeat(int* ret);
};
#endif // !VONAT_H