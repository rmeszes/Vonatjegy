#ifndef VONAT_H
#define VONAT_H

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

class Vonat {
	int vonat_szam;
	size_t kocsik_szama;
	String ind, erk, indido, erkido;
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


class Tarsasag {
public:
	void addVonat(Vonat& v) {}
	
	void listVonatok(std::ostream& os) const { os << "vonatok list�ja"; }

	void buyTicket(int vonatszam, SmartPtr<Jegy>& menetjegy, SmartPtr<Jegy>& helyjegy) {
		menetjegy = new Menetjegy(200, 123456789, 1000);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}
	void buyStudentTicket(int vonatszam, SmartPtr<Jegy>& diakjegy, SmartPtr<Jegy>& helyjegy, String ig_szam) {
		diakjegy = new Diakjegy(200, 123456789, 1000, ig_szam);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}

	void eladottJegyek(std::ostream& os) const { os << "jegyek list�z�sa"; }
};
#endif // !VONAT_H