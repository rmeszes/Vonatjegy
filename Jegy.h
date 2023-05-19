#ifndef JEGY_H
#define JEGY_H

#include <iostream>

#include "memtrace.h"
#include "string.h"

class Jegy {
public:
	Jegy(int ar, int szam, int vonat) {}
	virtual int getAr() const = 0;
	virtual int getszam() const = 0;
	virtual int getVonat() const = 0;
	virtual void kiir(std::ostream& os = std::cout) const = 0;
	virtual ~Jegy() {}
};

class Menetjegy :public Jegy {
public:
	Menetjegy(int ar, int szam, int vonat) :Jegy(ar, szam, vonat) {}
	int getAr() const { return 200; }
	int getszam() const { return 123456789; }
	int getVonat() const { return 1000; }
	void kiir(std::ostream& os = std::cout) const {
		os << "menetjegy vagyok\n";
	}
	~Menetjegy() {}
};

class Diakjegy :public Jegy {
public:
	Diakjegy(int ar, int szam, int vonat, String diakigazolvany) :Jegy(ar, szam, vonat) {}
	int getAr() const { return 20; }
	int getszam() const { return 123456789; }
	int getVonat() const { return 1000; }
	void kiir(std::ostream& os = std::cout) const {
		os << "diak_ig szam: " << "71613347453" << "\n";
	}
};

class Helyjegy : public Jegy {
public:
	Helyjegy(int ar, int szam, int vonat, int kocsi, int hely) :Jegy(ar, szam, vonat) {}
	int getAr() const { return 20; }
	int getszam() const { return 123456789; }
	int getVonat() const { return 1000; }
	void kiir(std::ostream& os = std::cout) const {
		os << "hely: " << 1 << "\n";
	}
};

#endif
