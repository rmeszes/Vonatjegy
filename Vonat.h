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

	void findSeat(int* ret) {
		ret[0] = 100;
		ret[1] = 1;
	}
};

class Jegy {
public:
	Jegy(int ar, int szam, int vonat) {}
	virtual int getAr() const { return 250; }
	virtual int getszam() const { return 123456789; }
	virtual int getVonat() const { return 1000; }
	virtual ~Jegy() {}
	virtual std::ostream& operator<<(std::ostream& os) const {
		return os << "jegy vagyok\n";
	}
};

class Menetjegy :public Jegy {
public:
	Menetjegy(int ar, int szam, int vonat) :Jegy(ar, szam, vonat) {}
	std::ostream& operator<<(std::ostream& os) const {
		return os << "menetjegy vagyok\n";
	}
	~Menetjegy() {}
};

class Diakjegy :public Jegy {
public:
	Diakjegy(int ar, int szam, int vonat, int diakigazolvany) :Jegy(ar, szam, vonat) {}
	std::ostream& operator<<(std::ostream& os) const {
		return os << "diak_ig szam: " << 123456789 << "\n";
	}
};

class Helyjegy : public Jegy {
public:
	Helyjegy(int ar, int szam, int vonat, int kocsi, int hely) :Jegy(ar, szam, vonat) {}
	std::ostream& operator<<(std::ostream& os) const {
		return os << "hely: " << 1 << "\n";
	}
};


class Tarsasag {
public:
	void addVonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, String ind, String erk, String indido, String erkido, int ar) {}
	
	void listVonatok(std::ostream& os) const { os << "vonatok listája"; }

	void buyTicket(int vonatszam, Jegy* menetjegy, Jegy* helyjegy) {
		menetjegy = new Menetjegy(200, 123456789, 1000);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}
	void buyStudentTicket(int vonatszam, Jegy* diakjegy, Jegy* helyjegy) {
		diakjegy = new Diakjegy(200, 123456789, 1000, 71613347453);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};
#endif // !VONAT_H