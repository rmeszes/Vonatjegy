#include <iostream>
#include <Windows.h>
#include <sstream>

#include "memtrace.h"
#include "gtest_lite.h"


#include "Vonat.h"
#include "List.hpp"
#include "string.h"
#include "SmartPtr.hpp"
#include "Tarsasag.h"
#include "Jegy.h"
#include "Menu.h"

int main() {
	//A windowsban a megfelelõ megjelenítéshez
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif

	Tarsasag tarsasag;
	Menu menu;
	menu.addItem(String("Uj vonat hozzadasa"), [&tarsasag]() {tarsasag.addVonat(); });
	menu.addItem(String("Vonatok kilistazasa"), [&tarsasag]() {tarsasag.listVonatok(); });
	menu.addItem(String("Teljesaru jegy vasarlasa"), [&tarsasag]() {tarsasag.buyTicket(); });
	menu.addItem(String("Diakjegy vasarlasa"), [&tarsasag]() {tarsasag.buyStudentTicket(); });
	menu.addItem(String("Eddig eladott jegyek"), [&tarsasag]() {tarsasag.eladottJegyek(); });
	menu.display();
	

#ifdef TESZTEK
	//tesztek ide
	//-------- Társaság class tesztjei
	Tarsasag t; //késõbb is kelleni fog
	List<Allomas> allomasok;
	allomasok.Add(Allomas("Budapest", "12:00"));
	allomasok.Add(Allomas("Miskolc", "14:00"));

	TEST(tarsasag, vonathozzaad) {
		//ez a teszt még felesleges, de érdemes ideírni, késõbb tesztelni kell
		ASSERT_NO_THROW(t.addVonat(Vonat(1000, 5, 30, 2000,allomasok)));
	} END;

	TEST(tarsasag, listvonatok) {
		std::stringstream ss;
		t.listVonatok(ss);
		std::string str = "vonatok listája";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, eladottjegyek) {
		std::stringstream ss;
		t.eladottJegyek(ss);
		std::string str = "jegyek listázása";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, menetjegyvasarlasa) {
		std::stringstream ss;
		SmartPtr<Jegy> menetjegy, hely;
		t.buyTicket(1000, menetjegy, hely, *allomasok.begin(), *allomasok.begin());
		menetjegy->kiir();
		hely->kiir();
	} END;

	TEST(tarsasag, diakjegyvasarlasa) {
		SmartPtr<Jegy> diakjegy, hely;
		t.buyStudentTicket(1000, diakjegy, hely, *allomasok.begin(), *allomasok.begin(), String("71613347453"));
		diakjegy->kiir();
		hely->kiir();
	} END;

	//-------- Jegy class tesztjei
	SmartPtr<Jegy> jegyek[3];
	TEST(jegy, letrehoz) {
		jegyek[0] = new Menetjegy(200, 12345678, 1000, *allomasok.begin(), *allomasok.begin());
		jegyek[1] = new Diakjegy(200, 12345678, 1000, *allomasok.begin(), *allomasok.begin(), String("71613347453"));
		jegyek[2] = new Helyjegy(200, 12345678, 1000, *allomasok.begin(), *allomasok.begin(), 100, 1);
		for (size_t i = 0; i < 3; i++) {
			jegyek[i]->kiir();
		}
	} END;

	TEST(jegy, fuggvenyek) {
		EXPECT_EQ(200, jegyek[0]->getAr());
		EXPECT_EQ(12345678, jegyek[1]->getszam());
		EXPECT_EQ(1000, jegyek[2]->getVonat());
	} END;

	//-------- Vonat class tesztjei
	
	TEST(vonat, fuggvenyek) {
		Vonat v(1000, 5, 30, 2000, allomasok);
		EXPECT_EQ(1000, v.getVonatSzam());
		EXPECT_EQ(2000, v.getAr());
		int seat[2];
		v.findSeat(seat);
		EXPECT_EQ(104, seat[0]);
		EXPECT_EQ(1, seat[1]);
	} END;

	TEST(kocsi, tesztek) {
		Kocsi k(100, 60);
		EXPECT_EQ(1, k.getHely());
		EXPECT_EQ(100, k.getKocsiSzam());
	} END;

#endif //!TESZTEK
	return 0;
}