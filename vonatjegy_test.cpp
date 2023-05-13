#include <iostream>
#include <Windows.h>

#include "memtrace.h"
#include "gtest_lite.h"


#include "Vonat.h"
#include "List.hpp"
#include "string.h"

int main() {
	//A windowsban a megfelel� megjelen�t�shez
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif

	//tesztek ide
	Tarsasag t; //k�s�bb is kelleni fog
	TEST(tarsasag, listvonatok) {
		std::stringstream ss;
		t.listVonatok(ss);
		std::string str = "vonatok list�ja";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, eladottjegyek) {
		std::stringstream ss;
		t.eladottJegyek(ss);
		std::string str = "jegyek list�z�sa";
		EXPECT_EQ(str, ss.str());
	} END;

	TEST(tarsasag, menetjegyvasarlasa) {
		std::stringstream ss;
		Jegy* menetjegy, * hely;
		t.buyTicket(1000, menetjegy, hely);
		ss << menetjegy << hely;
		std::string str = "menetjegy vagyok\nhely: 1\n";
		EXPECT_EQ(str, ss.str());
		delete menetjegy;
	} END;

	TEST(tarsasag, diakjegyvasarlasa) {
		std::stringstream ss;
		Jegy* diakjegy, * hely;
		t.buyStudentTicket(1000, diakjegy, hely);
		ss << diakjegy << hely;
		std::string str = "diak_ig: 12345678\nhely: 1\n";
		EXPECT_EQ(str, ss.str());
		delete diakjegy;
	} END;
	
	std::cout << "\nA k�d lefutott, Enter a bez�r�shoz";
	std::cin.get();
	return 0;
}