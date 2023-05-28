#include "Tarsasag.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <limits>
#include <memory>

#include "memtrace.h"

using std::cout;
//#define CPORTA
/*#if defined(CPORTA)//cporta esetén a user input kéréseket "némítom"
	//std::ifstream cin("test.txt");
	std::ofstream nullStream("nul");
	std::streambuf* oldBuffer = std::cout.rdbuf(nullStream.rdbuf());
#endif*/
	using std::cin;

/// <summary>
/// Egy pozitív egész szám bekérésére szolgál ami > 0
/// </summary>
/// <param name="bekert_adat">A felhasználónak segítség, hogy mit írjon be</param>
/// <param name="max">A maximum elfogadott szám. (nem kötelező)</param>
/// <param name="min">A minimum elfogadott szám. (nem kötelező)</param>
/// <returns>A sikeresen bekért szám</returns>
size_t getnum(const char* bekert_adat, size_t max = SIZE_MAX, size_t min = 0) {
	String buffer;
	size_t ret = 0;
	while (ret == 0) {
		cout << bekert_adat;
		bool valid = true;
		buffer.getline(cin);
		for (size_t i = 0; i < buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha már invalid ne fusson végig
		}
		if (valid == true) { // ha az összes elem szám, jöhet
			ret = strtoull(buffer.c_str(),nullptr, 10);
			if (ret > max) {
				cout << "A szam tul nagy!\n";
				ret = 0;
			}
			else if (ret < min) {
				cout << "A szam tul kicsi!\n";
				ret = 0;
			}
		}
		else {
			cout << "Hibas bemenet! (" << buffer << ")\n";
		}
	}
	return ret;
}


void Tarsasag::addVonat() {
	cout << "Uj vonat hozzaadasa" << std::endl;
	size_t kocsik_szama = getnum("Kocsik szama: ");

	size_t helyek_szama = getnum("Helyek szama: ");
	
	int ar = getnum("A vonat alapara allomasonkent: ");

	cout << "A vonat allomasai, enterrel elvalasztva, # a befejezo karakter\n";
	List<Allomas> allomasok;
	size_t allomasok_size = 0;

	String buffer;
	buffer.getline(cin);
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
		buffer.getline(cin);
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
		buffer.getline(cin);
		it->ido = buffer;
		++it;
	}
	vonatok.push_back(Vonat(vonatszam++, kocsik_szama, helyek_szama, ar, allomasok));
}


void Tarsasag::listVonatok(std::ostream& os) 
{
	if (vonatok.empty()) {
		os << "Meg nincsen vonat hozzaadva!\n";
	}
	else {
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
}

	
/// A felhasználótól addig kér be vonatszámot, amíg nem ír be egy létezőt
/// </summary>
/// <returns>A megfelelő vonat referenciája</returns>
Vonat& Tarsasag::findVonat() {
	Vonat* result = nullptr;
	while(true) {
		int valasztott_szam = (int)getnum("A valasztott vonat szama: ");
		for (auto& it : vonatok) {
			if (it.getVonatSzam() == valasztott_szam) {
				result = &it;
				break;
			}
		}
		if (result != nullptr) break;
		cout << "Nem talaltunk ilyen vonatot, kerlek probald ujra!\n";
	}
	return *result;
}



void Tarsasag::buyTicket()
{
	if (vonatok.empty()) {
		std::cout << "Meg nincsen vonat hozzaadva!\n";
	}
	else {
		cout << "Jegyvasarlas\n";
		listVonatok(cout);
		Vonat& vonat = findVonat();
		int hely[2];
		vonat.findSeat(hely);
		if (hely[0] != 0) { //ha van hely a vonaton
			cout << "Kerlek valassz indulo allomast!\n";
			size_t i = 0; // ebben számoljuk a kiírt állomások mennyiségét
			for (const auto& it : vonat.getAllomasok()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it.nev << it.ido << std::endl;
				++i;
			}
			size_t valasztott_all = getnum("Valasztott allomas sorszama: ", i - 1, 1) - 1; //az állomás sorszáma nem lehet az utolsó, vagy nagyobb, -1 az index miatt
			auto ind_all = vonat.getAllomasok().begin(); // ebben tároljuk, hogy majd melyik állomás lesz az induló
			double haladott_allomasok = 0;
			for (size_t j = 0; j != valasztott_all; j++) {
				++ind_all; //addig léptetjük az állomásokon, amíg el nem ér a választott indexre
			}
			cout << "Kerlek valassz erkezesi allomast!\n";
			i = 0; // ebben számoljuk a kiírt állomások mennyiségét
			auto it = ind_all; //lehetséges érkezési állomás már csak az indulási után jöhet
			++it; // hogy ne legyen a listán az indulási
			while (it != vonat.getAllomasok().end()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it->nev << it->ido << std::endl;
				++i;
				++it;
			}
			//az állomás sorszáma max annyi lehet, ahány állomás van, itt nincs mínusz egy, ezzel mindig továbblép a kövektező állomásra
			valasztott_all = getnum("Valasztott allomas sorszama: ", i, 1);
			auto erkezesi_all = ind_all; //az indulási állomástól kezdjük a számolást
			for (size_t j = 0; j < valasztott_all; j++) {
				++erkezesi_all;
				haladott_allomasok += 1;
			}

			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Menetjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, haladott_allomasok))); //a jegyek egy copyját eltárolja magának az objektum
			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Helyjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok)));

			cout << "Az eladott jegyek:\n";
			eladott_jegyek[eladott_jegyek.size() - 2]->kiir();
			eladott_jegyek[eladott_jegyek.size() - 1]->kiir();

		}
		else { // ha nincs hely a vonaton
			cout << "Sajnos a vonaton nem maradt hely!\n";
		}
	}
}



void Tarsasag::buyStudentTicket()
{
	if (vonatok.empty()) {
		std::cout << "Meg nincsen vonat hozzaadva!\n";
	}
	else {
		cout << "Jegyvasarlas\n";
		String ig_szam;
		cout << "Kerlek add meg a diakigazolvany szamod: ";
		ig_szam.getline(cin);
		listVonatok(cout);
		Vonat& vonat = findVonat();
		int hely[2];
		vonat.findSeat(hely);
		if (hely[0] != 0) { //ha van hely a vonaton
			cout << "Kerlek valassz indulo allomast!\n";
			size_t i = 0; // ebben számoljuk a kiírt állomások mennyiségét
			for (const auto& it : vonat.getAllomasok()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it.nev << it.ido << std::endl;
				++i;
			}
			size_t valasztott_all = getnum("Valasztott allomas sorszama: ", i - 1, 1) - 1; //az állomás sorszáma nem lehet az utolsó, vagy nagyobb, -1 az index miatt
			auto ind_all = vonat.getAllomasok().begin(); // ebben tároljuk, hogy majd melyik állomás lesz az induló
			double haladott_allomasok = 0;
			for (size_t j = 0; j != valasztott_all; j++) {
				++ind_all; //addig léptetjük az állomásokon, amíg el nem ér a választott indexre
			}
			cout << "Kerlek valassz erkezesi allomast!\n";
			i = 0; // ebben számoljuk a kiírt állomások mennyiségét
			auto it = ind_all; //lehetséges érkezési állomás már csak az indulási után jöhet
			++it; // hogy ne legyen a listán az indulási
			while (it != vonat.getAllomasok().end()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it->nev << it->ido << std::endl;
				++i;// ebben számoljuk a kiírt állomások mennyiségét
				++it; //ékezési állomás lesz
			}
			//az állomás sorszáma max annyi lehet, ahány állomás van, itt nincs mínusz egy, ezzel mindig továbblép a kövektező állomásra
			valasztott_all = getnum("Valasztott allomas sorszama: ", i, 1);
			auto erkezesi_all = ind_all; //az indulási állomástól kezdjük a számolást
			for (size_t j = 0; j < valasztott_all; ++j) {
				++erkezesi_all;
				haladott_allomasok += 1;
			}

			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Diakjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, ig_szam, haladott_allomasok))); //a jegyek egy copyját eltárolja magának az objektum
			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Helyjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok)));

			cout << "Az eladott jegyek:\n";
			eladott_jegyek[eladott_jegyek.size() - 2]->kiir();
			eladott_jegyek[eladott_jegyek.size() - 1]->kiir();
		}
		else { // ha nincs hely a vonaton
			cout << "Sajnos a vonaton nem maradt hely!\n";
		}
	}
}


void Tarsasag::eladottJegyek(std::ostream& os)
{
	if (eladott_jegyek.empty()) {
		std::cout << "Meg nincs eladott jegy!\n";
	}
	else {
		cout << "Eladott jegyek:\n";
		for (auto& it : eladott_jegyek) {
			it->kiir(os);
		}
	}
}
