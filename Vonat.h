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

class Jegy {
	Vonat& vonat;
public:
	Jegy(int ar, int szam, Vonat& vonat) :vonat(vonat) {}
	virtual int getAr() const { return 250; }
	virtual int getszam() const { return 123456789; }
	virtual Vonat& getVonat() const { return vonat; }
	virtual ~Jegy() {}
	virtual void kiir(std::ostream& os) const { os << "jegy vagyok"; }
};

class Menetjegy :public Jegy {
public:
	Menetjegy(int ar, int szam, Vonat& vonat) :Jegy(ar, szam, vonat) {}
};

class Diakjegy :public Jegy {
public:
	Diakjegy(int ar, int szam, Vonat& vonat, int diakigazolvany) :Jegy(ar, szam, vonat) {}
	void kiir(std::ostream& os) const {
		os << "diakjegy vagyok";
	}
};


class Tarsasag {
	List<Vonat> vonatok;
public:
	void addVonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, String ind, String erk, String indido, String erkido, int ar) {
		vonatok.Add(Vonat(1000, 1, 60, "", "", "", "", 200));
	}
	
	void listVonatok(std::ostream& os) const { os << "vonatok listája"; }

	void buyTicket(int vonatszam, Jegy* ret) { ret = new Menetjegy(200, 123456789, *vonatok[0]); }
	void buyStudentTicket(int vonatszam, Jegy* ret) { ret = new Diakjegy(200, 123456789, *vonatok[0], 71613347453); }

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};
#endif // !VONAT_H