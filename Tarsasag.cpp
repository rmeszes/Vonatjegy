#include "Tarsasag.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <limits>
#include <memory>

#include "memtrace.h"

using std::cin;
using std::cout;

/// <summary>
/// Egy szam bek�r�s�re szolg�l
/// </summary>
/// <param name="bekert_adat">A felhaszn�l� sz�m�ra ki�rt �zenet, ami le�rja mit k�r a program</param>
/// <returns>Egy eg�sz sz�m</returns>
size_t getnum(const char* bekert_adat, size_t max = SIZE_MAX, size_t min = 0) {
	String buffer;
	size_t ret = 0;
	while (ret == 0) {
		cout << bekert_adat;
		bool valid = true;
		buffer.getline();
		for (size_t i = 0; i < buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha m�r invalid ne fusson v�gig
		}
		if (valid == true) { // ha az �sszes elem sz�m, j�het
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

	cout << "A vonat allomasai, enterrel elvalasztva, # a bejezez� karakter\n";
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

Vonat& Tarsasag::findVonat() {
	Vonat* result = nullptr;
	while(true) {
		int vonatszam = (int)getnum("A valasztott vonat szama: ");
		for (auto& it : vonatok) {
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
			size_t i = 0; // ebben sz�moljuk a ki�rt �llom�sok mennyis�g�t
			for (auto& it : vonat.getAllomasok()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it.nev << it.ido << std::endl;
				i++;
			}
			size_t valasztott_all = getnum("Valasztott allomas sorszama: ", i - 1, 1) - 1; //az �llom�s sorsz�ma nem lehet az utols�, vagy nagyobb, -1 az index miatt
			auto ind_all = vonat.getAllomasok().begin(); // ebben t�roljuk, hogy majd melyik �llom�s lesz az indul�
			double haladott_allomasok = 1;
			for (size_t j = 0; j != valasztott_all; j++) {
				ind_all++; //addig l�ptetj�k az �llom�sokon, am�g el nem �r a v�lasztott indexre
				haladott_allomasok += 1;
			}
			cout << "Kerlek valassz erkezesi allomast!\n";
			i = 0; // ebben sz�moljuk a ki�rt �llom�sok mennyis�g�t
			auto it = ind_all; //lehets�ges �rkez�si �llom�s m�r csak az indul�si ut�n j�het
			it++; // hogy ne legyen a list�n az indul�si
			while (it != vonat.getAllomasok().end()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it->nev << it->ido << std::endl;
				i++;
				it++;
			}
			//az �llom�s sorsz�ma max annyi lehet, ah�ny �llom�s van, itt nincs m�nusz egy, ezzel mindig tov�bbl�p a k�vektez� �llom�sra
			valasztott_all = getnum("Valasztott allomas sorszama: ", i, 1);
			auto erkezesi_all = ind_all; //az indul�si �llom�st�l kezdj�k a sz�mol�st
			for (size_t j = 0; j != i; j++) {
				erkezesi_all++;
			}
			menetjegy = new Menetjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, haladott_allomasok); // ki�rjuk a jegyeket a param�terben megadott pointerbe
			helyjegy = new Helyjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok);

			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Menetjegy(vonat.getAr(), jegyszam - 2, vonat.getVonatSzam(), *ind_all, *erkezesi_all, haladott_allomasok))); //a jegyek egy copyj�t elt�rolja mag�nak az objektum
			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Helyjegy(vonat.getAr(), jegyszam - 1, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok)));

			cout << "Az eladott jegyek:\n";
			menetjegy->kiir();
			helyjegy->kiir();
		}
		else { // ha nincs hely a vonaton
			cout << "Sajnos a vonaton nem maradt hely!";
		}
	}
}

void Tarsasag::buyStudentTicket(SmartPtr<Jegy>& menetjegy, SmartPtr<Jegy>& helyjegy)
{
	if (vonatok.empty()) {
		std::cout << "Meg nincsen vonat hozzaadva!\n";
	}
	else {
		cout << "Jegyvasarlas\n";
		String ig_szam;
		cout << "Kerlek add meg a diakigazolvany szamod: ";
		ig_szam.getline();
		listVonatok(cout);
		Vonat& vonat = findVonat();
		int hely[2];
		vonat.findSeat(hely);
		if (hely[0] != 0) { //ha van hely a vonaton
			cout << "Kerlek valassz indulo allomast!\n";
			size_t i = 0; // ebben sz�moljuk a ki�rt �llom�sok mennyis�g�t
			for (auto& it : vonat.getAllomasok()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it.nev << it.ido << std::endl;
				i++;
			}
			size_t valasztott_all = getnum("Valasztott allomas sorszama: ", i - 1, 1) - 1; //az �llom�s sorsz�ma nem lehet az utols�, vagy nagyobb, -1 az index miatt
			auto ind_all = vonat.getAllomasok().begin(); // ebben t�roljuk, hogy majd melyik �llom�s lesz az indul�
			double haladott_allomasok = 1;
			for (size_t j = 0; j != valasztott_all; j++) {
				ind_all++; //addig l�ptetj�k az �llom�sokon, am�g el nem �r a v�lasztott indexre
				haladott_allomasok += 1;
			}
			cout << "Kerlek valassz erkezesi allomast!\n";
			i = 0; // ebben sz�moljuk a ki�rt �llom�sok mennyis�g�t
			auto it = ind_all; //lehets�ges �rkez�si �llom�s m�r csak az indul�si ut�n j�het
			it++; // hogy ne legyen a list�n az indul�si
			while (it != vonat.getAllomasok().end()) {
				cout << i + 1 << " " << std::left << std::setw(20) << std::setfill(' ') << it->nev << it->ido << std::endl;
				i++;// ebben sz�moljuk a ki�rt �llom�sok mennyis�g�t
				it++; //�kez�si �llom�s lesz
			}
			//az �llom�s sorsz�ma max annyi lehet, ah�ny �llom�s van, itt nincs m�nusz egy, ezzel mindig tov�bbl�p a k�vektez� �llom�sra
			valasztott_all = getnum("Valasztott allomas sorszama: ", i, 1);
			auto erkezesi_all = ind_all; //az indul�si �llom�st�l kezdj�k a sz�mol�st
			for (size_t j = 0; j != i; j++) {
				erkezesi_all++;
			}
			menetjegy = new Diakjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, ig_szam, haladott_allomasok); // ki�rjuk a jegyeket a param�terben megadott pointerbe
			helyjegy = new Helyjegy(vonat.getAr(), jegyszam++, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok);

			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Diakjegy(vonat.getAr(), jegyszam - 2, vonat.getVonatSzam(), *ind_all, *erkezesi_all, ig_szam, haladott_allomasok))); //a jegyek egy copyj�t elt�rolja mag�nak az objektum
			eladott_jegyek.push_back(std::shared_ptr<Jegy>(new Helyjegy(vonat.getAr(), jegyszam - 1, vonat.getVonatSzam(), *ind_all, *erkezesi_all, hely[0], hely[1], haladott_allomasok)));

			cout << "Az eladott jegyek:\n";
			menetjegy->kiir();
			helyjegy->kiir();
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
			it->kiir();
		}
	}
}
