#ifndef TARSASAG_H
#define TARSASAG_H

#include "memtrace.h"
#include "string.h"
#include "SmartPtr.hpp"
#include "Vonat.h"
#include "Jegy.h"

class Tarsasag {
	int jegyszam;
	int vonatszam;
	List<Vonat> vonatok;
	List<SmartPtr<Jegy>> eladott_jegyek;
public:
	Tarsasag() :jegyszam(1000000), vonatszam(1000) {}

	void addVonat();

	void listVonatok(std::ostream& os); //TODO const

	void buyTicket();
	void buyStudentTicket();

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};

#endif
