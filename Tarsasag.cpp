#include "Tarsasag.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>

#include "memtrace.h"

using std::cin;
using std::cout;

/// <summary>
/// Egy szam bekérésére szolgál
/// </summary>
/// <param name="bekert_adat">A felhasználó számára kiírt üzenet, ami leírja mit kér a program</param>
/// <returns>Egy egész szám</returns>
size_t getnum(const char* bekert_adat) {
	String buffer;
	size_t ret = 0;
	while (ret == 0) {
		cout << bekert_adat;
		bool valid = true;
		buffer.getline();
		for (size_t i = 0; i < buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha már invalid ne fusson végig
		}
		if (valid == true) { // ha az összes elem szám, jöhet
			ret = strtoull(buffer.c_str(),nullptr, 10);
		}
		else {
			cout << "Hibas bemenet! (" << buffer << ")\n";
		}
		// TODO solve throwing away the buffer, only if its not empty
	}
	return ret;
}



void Tarsasag::addVonat() {
	cout << "Uj vonat hozzaadasa" << std::endl;
	size_t kocsik_szama = getnum("Kocsik szama: ");

	size_t helyek_szama = getnum("Helyek szama: ");
	
	int ar = getnum("A vonat alap menetjegy ara: ");

	cout << "A vonat allomasai, enterrel elvalasztva, # a bejezezõ karakter\n";
	List<Allomas> allomasok;
	size_t allomasok_size = 0;

	String buffer;
	buffer.getline();
	while (buffer.c_str()[0] != '#' || allomasok_size < 2) {
		if (buffer.c_str()[0] == '#') {
			cout << "Legalabb 2 allomast hozza kell adni!" << std::endl;
		}
		else {
			if (buffer.size() > 0) {
				allomasok.push_back(Allomas(buffer, String()));
				allomasok_size++;
			}
		}
		buffer.getline();
	}

	cout << "Indulasi/erkezesi idok\n";
	auto it = allomasok.begin();
	for (size_t i = 0; i < allomasok_size; i++) {
		if (i != allomasok_size-1) {
			cout << "Indulas (" << it->nev << "): ";
		}
		else {
			cout << "Erkezes (" << it->nev << "): ";
		}
		buffer.getline();
		it->ido = buffer;
		it++;
	}
	vonatok.push_back(Vonat(vonatszam++, kocsik_szama, helyek_szama, ar, allomasok));
}

void Tarsasag::listVonatok(std::ostream& os) 
{
	os << "Vonatok listaja:\n";
	os << std::left << std::setw(5) << std::setfill(' ') << "Vonat" << " | ";
	os << std::left << std::setw(20) << std::setfill(' ') << "Indulasi allomas" << " | ";
	os << std::left << std::setw(20) << std::setfill(' ') << "Vegallomas" << " | ";
	os << std::left << std::setw(12) << std::setfill(' ') << "Indulasi ido" << " | ";
	os << std::left << std::setw(12) << std::setfill(' ') << "Erkezesi ido" << " | ";
	os << std::right << std::setw(9) << std::setfill(' ') << "Alap ar" << " | ";
	os << std::endl;

	for (auto& it : vonatok) {
		os << std::left << std::setw(5) << std::setfill(' ') << it.getVonatSzam() << " | ";
		os << std::left << std::setw(20) << std::setfill(' ') << it.induloAll() << " | ";
		os << std::left << std::setw(20) << std::setfill(' ') << it.vegallomas() << " | ";
		os << std::left << std::setw(12) << std::setfill(' ') << it.indIdo() << " | ";
		os << std::left << std::setw(12) << std::setfill(' ') << it.erkIdo() << " | ";
		os << std::right << std::setw(7) << std::setfill(' ') << it.getAr() << "Ft" << " | ";
		os << std::endl;
	}
}

Vonat& Tarsasag::findVonat() {
	Vonat* result = nullptr;
	while(true) {
		int vonatszam = (int)getnum("A valasztott vonat szama: ");
		for (auto it : vonatok) {
			if (it.getVonatSzam() == vonatszam) {
				result = &it;
				break;
			}
		}
		if (result != nullptr) break;
		cout << "Nem talaltunk ilyen vonatot, kerlek probald ujra!\n";
	}
	return *result;
}

void Tarsasag::buyTicket(SmartPtr<Jegy>& menetjegy, SmartPtr<Jegy>& helyjegy) 
{
	cout << "Jegyvasarlas";
	cout << "A valaszthato vonatok: ";
	listVonatok(cout);
	Vonat& vonat = findVonat();
	int hely[2];
	vonat.findSeat(hely);
	if (hely[0] != 0) { //ha van hely a vonaton

	}
	else { // ha nincs hely a vonaton
		cout << "Sajnos a vonaton nem maradt hely!";
	}
}
