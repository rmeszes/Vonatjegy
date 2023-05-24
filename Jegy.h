#ifndef JEGY_H
#define JEGY_H

#include <iostream>

#include "memtrace.h"
#include "string.h"

class Jegy {
protected:
	static int sorszam;
	double ar;
	int szam, vonat;
	String allomas1, allomas2, ind_ido, erk_ido;
	double allomasok;
public:
	Jegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, double allomasok)
		:ar(ar), szam(szam), vonat(vonat), allomas1(ind.nev), allomas2(erk.nev), ind_ido(ind.ido), erk_ido(erk.ido), allomasok(allomasok) {}
	virtual double getAr() const = 0;
	virtual int getszam() const = 0;
	virtual int getVonat() const = 0;
	virtual void kiir(std::ostream& os = std::cout) const = 0;
	virtual ~Jegy() {}
};

class Menetjegy :public Jegy {
public:
	Menetjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, double allomasok) :Jegy(ar, szam, vonat, ind, erk, allomasok) {}
	double getAr() const { return ar * allomasok; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Jegyszam: " << szam << std::endl;
		os << "Menetjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl;
		os << "Ar: " << getAr() << std::endl;
	}
	~Menetjegy() {}
};

class Diakjegy :public Jegy {
	String ig_szam;
public:
	Diakjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, String& diakigazolvany, double allomasok) :Jegy(ar, szam, vonat, ind, erk, allomasok), ig_szam(diakigazolvany) {}
	double getAr() const { return ar * 0.1 * allomasok; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Jegyszam: " << szam << std::endl;
		os << "Diakjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl << "\tDiakigazolvany szam: " << ig_szam << std::endl;
		os << "Ar: " << getAr() << std::endl;
	}
};

class Helyjegy : public Jegy {
	int kocsi, hely;
public:
	Helyjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, int kocsi, int hely, double allomasok) :Jegy(ar, szam, vonat, ind, erk, allomasok), kocsi(kocsi), hely(hely) {}
	double getAr() const { return ar * 0.2 * allomasok; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Jegyszam: " << szam << std::endl;
		os << "Helyjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl << "\tKocsi: " << kocsi << " Hely: " << hely << std::endl;
		os << "Ar: " << getAr() << std::endl;
	}
};

#endif
