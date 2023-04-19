#ifndef VONAT_H
#define VONAT_H

#include "List.hpp"
#include "string.h"

class Kocsi {
	unsigned int kocsi_szam; 
	size_t helyek;
public:
	Kocsi(unsigned int kocsi_szam, size_t helyek_szama) :kocsi_szam(kocsi_szam), helyek(helyek_szama) {}
	unsigned int getKocsiSzam() const { return kocsi_szam; }
	size_t getHelyekSzama() const { return helyek; }
};

class Vonat {
	unsigned int vonat_szam;
	List<Kocsi> kocsik;
public:
	Vonat(unsigned int vonat_szam, size_t kocsik_szama, size_t helyek_szama) :vonat_szam(vonat_szam) {
		for (size_t i = 0; i < kocsik_szama; i++)
		{
			kocsik.Add(Kocsi(100 + i, helyek_szama));
		}
	}
	unsigned int getVonatSzam() const { return vonat_szam; }
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