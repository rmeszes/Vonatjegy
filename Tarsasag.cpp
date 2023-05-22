#include "Tarsasag.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits

#include "memtrace.h"

using std::cin;
using std::cout;

void Tarsasag::addVonat() {
	cout << "Uj vonat hozzaadasa" << std::endl;
	String buffer;
	size_t kocsik_szama = 0;
	while (kocsik_szama == 0) {
		cout << "\tKocsik szama: ";
		bool valid = true;
		cin >> buffer;
		for (size_t i = 0; buffer.size(); i++) {
			if(!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha m�r invalid ne fusson v�gig
		}
		if (valid == true) { // ha az �sszes elem sz�m, j�het
			kocsik_szama = (size_t)atoi(buffer.c_str());
		} 
		else {
			cout << "\tHibas bemenet! (" << buffer << ")\n";
		}
		// TODO solve throwing away the buffer, only if its not empty
	}

	size_t helyek_szama = 0;
	while (helyek_szama == 0) {
		cout << "\tHelyek szama: ";
		bool valid = true;
		cin >> buffer;
		for (size_t i = 0; buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha m�r invalid ne fusson v�gig
		}
		if (valid == true) { // ha az �sszes elem sz�m, j�het
			helyek_szama = (size_t)atoi(buffer.c_str());
		}
		else {
			cout << "\tHibas bemenet! (" << buffer << ")\n";
		}
		if (!cin.eof()) {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //mivel a String oszt�ly csak wspace-ig olvas, eldobjuk a t�bbit
		}
	}
	
	int ar = 0;
	while (ar == 0) {
		cout << "\tA menetjegy alap ara: ";
		bool valid = true;
		cin >> buffer;
		for (size_t i = 0; buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha m�r invalid ne fusson v�gig
		}
		if (valid == true) { // ha az �sszes elem sz�m, j�het
			ar = atoi(buffer.c_str());
		}
		else {
			cout << "\tHibas bemenet! (" << buffer << ")\n";
		}
		if (!cin.eof()) {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //mivel a String oszt�ly csak wspace-ig olvas, eldobjuk a t�bbit
		}
	}

	cout << "\tA vonat allomasai, enterrel elvalasztva, # a bejezez� karakter\n";
	List<Allomas> allomasok;
	size_t allomasok_size = 0;
	cin >> buffer;
	while (buffer.c_str()[0] != '#' && allomasok_size >= 2) {
		if (buffer.c_str()[0] == '#') {
			cout << "Legalabb ket allomasa kell legyen egy vonatnak!";
		}
		while (!cin.eof()) { // egy �llom�snak a nev�ben lehet space, ez�rt tov�bb kell olvassuk eof-ig
			buffer + cin.get();
		}
		allomasok.Add(Allomas(buffer));
	}
	
	vonatok.Add(Vonat(vonatszam++, kocsik_szama, helyek_szama, ar, allomasok));
}