#ifndef TARSASAG_H
#define TARSASAG_H

#include "memtrace.h"
#include "string.h"
#include "SmartPtr.hpp"
#include "Vonat.h"
#include "Jegy.h"

class Tarsasag {
public:
	void addVonat(Vonat& v) {}

	void listVonatok(std::ostream& os) const { os << "vonatok listája"; }

	void buyTicket(int vonatszam, SmartPtr<Jegy>& menetjegy, SmartPtr<Jegy>& helyjegy) {
		menetjegy = new Menetjegy(200, 123456789, 1000);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}
	void buyStudentTicket(int vonatszam, SmartPtr<Jegy>& diakjegy, SmartPtr<Jegy>& helyjegy, String ig_szam) {
		diakjegy = new Diakjegy(200, 123456789, 1000, ig_szam);
		helyjegy = new Helyjegy(200, 987654321, 1000, 100, 1);
	}

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};

#endif
