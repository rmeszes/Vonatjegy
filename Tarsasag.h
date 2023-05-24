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
	List<std::shared_ptr<Jegy>> eladott_jegyek;

	Vonat& findVonat();
public:
	Tarsasag() :jegyszam(1000000), vonatszam(1000) {}

	void addVonat();

	void listVonatok(std::ostream& os = std::cout); 

	void buyTicket(SmartPtr<Jegy>& menetjegy = SmartPtr<Jegy>(), SmartPtr<Jegy>& helyjegy = SmartPtr<Jegy>());
	void buyStudentTicket(SmartPtr<Jegy>& menetjegy = SmartPtr<Jegy>(), SmartPtr<Jegy>& helyjegy = SmartPtr<Jegy>());

	void eladottJegyek(std::ostream& os) const { os << "jegyek listázása"; }
};

#endif
