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

int main() {
	//A windowsban a megfelelõ megjelenítéshez
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif

	//tesztek ide

	//-------- Társaság class tesztjei
	Tarsasag t; //késõbb is kelleni fog

	TEST(tarsasag, vonathozzaad) {
		//ez a teszt még felesleges, de érdemes ideírni, késõbb tesztelni kell
		List<Allomas> allomasok;
		allomasok.Add(Allomas("Budapest","12:00"));
		allomasok.Add(Allomas("Miskolc","14:00"));
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
		t.buyTicket(1000, menetjegy, hely);
		menetjegy->kiir(ss);
		hely->kiir(ss);
		std::string str = "menetjegy vagyok\nhely: 1\n";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, diakjegyvasarlasa) {
		std::stringstream ss;
		SmartPtr<Jegy> diakjegy, hely;
		t.buyStudentTicket(1000, diakjegy, hely, String("71613347453"));
		diakjegy->kiir(ss);
		hely->kiir(ss);
		std::string str = "diak_ig szam: 71613347453\nhely: 1\n";
		EXPECT_EQ(str, ss.str());
	} END;

	//-------- Jegy class tesztjei
	SmartPtr<Jegy> jegyek[3];
	TEST(jegy, letrehoz) {
		jegyek[0] = new Menetjegy(200, 12345678, 1000);
		jegyek[1] = new Diakjegy(200, 12345678, 1000, String("71613347453"));
		jegyek[2] = new Helyjegy(200, 12345678, 1000, 100, 1);
		
		std::stringstream ss;
		for (size_t i = 0; i < 3; i++) {
			jegyek[i]->kiir(ss);
		}
		std::string str("menetjegy vagyok\ndiak_ig szam: 71613347453\nhely: 1\n");
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(jegy, fuggvenyek) {
		EXPECT_EQ(200, jegyek[0]->getAr());
		EXPECT_EQ(123456789, jegyek[1]->getszam());
		EXPECT_EQ(1000, jegyek[2]->getVonat());
	} END;

	//-------- Vonat class tesztjei
	
	TEST(vonat, fuggvenyek) {
		List<Allomas> allomasok;
		allomasok.Add(Allomas("Budapest", "12:00"));
		allomasok.Add(Allomas("Miskolc", "14:00"));
		Vonat v(1000, 5, 30, 2000, allomasok);
		EXPECT_EQ(1000, v.getVonatSzam());
		EXPECT_EQ(2000, v.getAr());
		int seat[2];
		v.findSeat(seat);
		EXPECT_EQ(100, seat[0]);
		EXPECT_EQ(1, seat[1]);
	} END;

	TEST(kocsi, tesztek) {
		Kocsi k(100, 60);
		EXPECT_EQ(1, k.getHely());
		EXPECT_EQ(100, k.getKocsiSzam());
	} END;
	
	std::cout << "\nA kód lefutott, Enter a bezáráshoz";
	std::cin.get();
	return 0;
}