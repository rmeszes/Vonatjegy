#include <iostream>
#include <Windows.h>
#include <sstream>

#include "memtrace.h"
#include "gtest_lite.h"


#include "Vonat.h"
#include "List.hpp"
#include "string.h"
#include "SmartPtr.hpp"

int main() {
	//A windowsban a megfelelõ megjelenítéshez
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif

	//tesztek ide
	Tarsasag t; //késõbb is kelleni fog
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
		t.buyStudentTicket(1000, diakjegy, hely);
		diakjegy->kiir(ss);
		hely->kiir(ss);
		std::string str = "diak_ig szam: 123456789\nhely: 1\n";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, vonathozzaad) {
		ASSERT_NO_THROW(t.addVonat(1000, 5, 30, String("Budapest"), String("Miskolc"), String("12:00"), String("14:00"), 2000));
	} END;
	
	std::cout << "\nA kód lefutott, Enter a bezáráshoz";
	std::cin.get();
	return 0;
}