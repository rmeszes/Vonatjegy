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
public:
	Jegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk) :ar(ar), szam(szam), vonat(vonat), allomas1(ind.nev), allomas2(erk.nev), ind_ido(ind.ido), erk_ido(erk.ido) {}
	virtual double getAr() const = 0;
	virtual int getszam() const = 0;
	virtual int getVonat() const = 0;
	virtual void kiir(std::ostream& os = std::cout) const = 0;
	virtual ~Jegy() {}
};

class Menetjegy :public Jegy {
public:
	Menetjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk) :Jegy(ar, szam, vonat, ind, erk) {}
	double getAr() const { return ar; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Menetjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl;
	}
	~Menetjegy() {}
};

class Diakjegy :public Jegy {
	String ig_szam;
public:
	Diakjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, String& diakigazolvany) :Jegy(ar, szam, vonat, ind, erk), ig_szam(diakigazolvany) {}
	double getAr() const { return ar * 0.1; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Diakjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl << "Diakigazolvany szam: " << ig_szam << std::endl;
	}
};

class Helyjegy : public Jegy {
	int kocsi, hely;
public:
	Helyjegy(double ar, int szam, int vonat, Allomas& ind, Allomas& erk, int kocsi, int hely) :Jegy(ar, szam, vonat, ind, erk), kocsi(kocsi), hely(hely) {}
	double getAr() const { return ar * 0.2; }
	int getszam() const { return szam; }
	int getVonat() const { return vonat; }
	void kiir(std::ostream& os = std::cout) const {
		os << "Helyjegy\n\t" << allomas1 << " - " << allomas2 << "\n\t" << ind_ido << " - " << erk_ido << std::endl << "Kocsi: " << kocsi << " Hely: " << hely << std::endl;
	}
};

#endif
