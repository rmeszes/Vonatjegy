#ifndef TARSASAG_H
#define TARSASAG_H

#include "memtrace.h"
#include "string.h"
#include "Vonat.h"
#include "Jegy.h"

class Tarsasag {
	int jegyszam;
	int vonatszam;
	List<Vonat> vonatok;
	List<std::shared_ptr<Jegy>> eladott_jegyek;

	Vonat& findVonat();
public:
	Tarsasag() :jegyszam(1000000), vonatszam(1000) {}

	void addVonat();

	void listVonatok(std::ostream& os = std::cout); 

	void buyTicket();
	void buyStudentTicket();

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};

#endif
