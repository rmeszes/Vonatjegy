#ifndef VONAT_H
#define VONAT_H

#include "List.hpp"
#include "string.h"
#include "Ido.h"

class Kocsi {
	unsigned int kocsi_szam; 
	bool* helyek;
	size_t helyek_szama;
public:
	Kocsi(unsigned int kocsi_szam = 0, size_t helyek_szama = 0) :kocsi_szam(kocsi_szam), helyek_szama(helyek_szama) {
		if (helyek_szama == 0) { helyek = nullptr; }
		else { helyek = new bool[helyek_szama]; }
		for (size_t i = 0; i < helyek_szama; i++) //inicializálom a tömb elemeit, hogy biztosan false legyen
		{
			helyek[i] = false;
		}
	}

	Kocsi(const Kocsi& k) :kocsi_szam(k.kocsi_szam), helyek_szama(k.helyek_szama) {
		helyek = new bool[helyek_szama];
		for (size_t i = 0; i < helyek_szama; i++)
		{
			this->helyek[i] = k.helyek[i];
		}
	}

	Kocsi& operator=(const Kocsi& k);

	~Kocsi() { delete[] helyek; }

	unsigned int getKocsiSzam() const { return kocsi_szam; }

	unsigned int getHely() const;

	bool* getHelyek() const { return helyek; }
};

class Vonat {
	unsigned int vonat_szam;
	List<Kocsi> kocsik;
	size_t kocsik_szama;
public:
	Vonat(unsigned int vonat_szam, size_t kocsik_szama, size_t helyek_szama) :vonat_szam(vonat_szam), kocsik_szama(kocsik_szama), kocsik() {
		for (size_t i = 0; i < kocsik_szama; i++) //elkészítjük a kocsikat
		{
			kocsik.Add(Kocsi(100 + i, helyek_szama));
		}
	}

	Vonat(const Vonat& v) :vonat_szam(v.vonat_szam), kocsik(v.kocsik), kocsik_szama(v.kocsik_szama) {}

	unsigned int getVonatSzam() const { return vonat_szam; }

	void findSeat(unsigned int* ret);

	~Vonat() {}
};


///  Még csak ötlet, lehet kidobom
/*class Jegy {
	int kocsi_szam; //csak a kiíráshoz kell
	int hely_szam;
};

class Vonal {
	Vonat* vonat;
	List<Jegy> jegyek;
	
	unsigned int indulasi_ido; //Esetleg egy idõt kezelõ class
	unsigned int erkezesi_ido;

	String indulasi_allomas;
	String erkezesi_allomas;
};

class Tarsasag {
	List<String> allomasok;
	List<std::unique_ptr<Vonat>> vonatok;
	List<Vonal> vonalak;
};*/

#endif // !VONAT_H