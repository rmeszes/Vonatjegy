#include "Tarsasag.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits

#include "memtrace.h"

using std::cin;
using std::cout;

size_t getnum(String& bekert_adat) {
	String buffer;
	size_t ret = 0;
	while (ret == 0) {
		cout << "\t" << bekert_adat;
		bool valid = true;
		cin >> buffer;
		for (size_t i = 0; i < buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha már invalid ne fusson végig
		}
		if (valid == true) { // ha az összes elem szám, jöhet
			ret = strtoull(buffer.c_str(),nullptr, 10);
		}
		else {
			cout << "\tHibas bemenet! (" << buffer << ")\n";
		}
		// TODO solve throwing away the buffer, only if its not empty
	}
	return ret;
}

void Tarsasag::addVonat() {
	cout << "Uj vonat hozzaadasa" << std::endl;
	size_t kocsik_szama = getnum(String("Kocsik szama: "));

	size_t helyek_szama = getnum(String("Helyek szama: "));
	
	int ar = getnum(String("A vonat alap menetjegy ara: "));

	cout << "\tA vonat allomasai, enterrel elvalasztva, # a bejezezõ karakter\n";
	List<Allomas> allomasok;
	size_t allomasok_size = 0;

	String buffer;
	char mini_buff;
	cin.get(mini_buff);
	while (mini_buff != '\n') { // egy állomásnak a nevében lehet space, ezért tovább kell olvassuk eof-ig
		buffer = buffer + mini_buff;
		cin.get(mini_buff);
	}
	while (buffer.c_str()[0] != '#' || allomasok_size < 2) {
		if (buffer.c_str()[0] == '#') {
			cout << "Legalabb 2 allomast hozza kell adni!" << std::endl;
		}
		else {
			allomasok.Add(Allomas(buffer, String()));
			allomasok_size++;
		}
		buffer = String();
		cin.get(mini_buff);
		while (mini_buff != '\n') { // egy állomásnak a nevében lehet space, ezért tovább kell olvassuk eof-ig
			buffer = buffer + mini_buff;
			cin.get(mini_buff);
		}
	}
	
	vonatok.Add(Vonat(vonatszam++, kocsik_szama, helyek_szama, ar, allomasok));
}


/*while (helyek_szama == 0) {
		cout << "\tHelyek szama: ";
		bool valid = true;
		cin >> buffer;
		for (size_t i = 0; buffer.size(); i++) {
			if (!isdigit(buffer.c_str()[i])) valid = false;
			if (valid == false) break; // ha már invalid ne fusson végig
		}
		if (valid == true) { // ha az összes elem szám, jöhet
			helyek_szama = (size_t)atoi(buffer.c_str());
		}
		else {
			cout << "\tHibas bemenet! (" << buffer << ")\n";
		}
		if (!cin.eof()) {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //mivel a String osztály csak wspace-ig olvas, eldobjuk a többit
		}
	}*/