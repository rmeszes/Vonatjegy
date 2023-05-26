#include <iostream>
#include <sstream>

#include "memtrace.h"
#include "gtest_lite.h"


#include "Vonat.h"
#include "List.hpp"
#include "string.h"
#include "Tarsasag.h"
#include "Jegy.h"
#include "Menu.h"
#include "string5_test.h"

#define CPORTA

int releaseMain() {
	Tarsasag tarsasag;
	Menu menu;
	menu.addItem(String("Uj vonat hozzadasa"), [&tarsasag]() {tarsasag.addVonat(); });
	menu.addItem(String("Vonatok kilistazasa"), [&tarsasag]() {tarsasag.listVonatok(); });
	menu.addItem(String("Teljesaru jegy vasarlasa"), [&tarsasag]() {tarsasag.buyTicket(); });
	menu.addItem(String("Diakjegy vasarlasa"), [&tarsasag]() {tarsasag.buyStudentTicket(); });
	menu.addItem(String("Eddig eladott jegyek"), [&tarsasag]() {tarsasag.eladottJegyek(); });
	menu.display();
	return 0;
}

int testMain() {
	//A listának csak használt függvényei vannak bent, külön nem igényel tesztelést

	string_tests();

	TEST(menu, all) {
		Tarsasag tarsasag;
		Menu menu;
		ASSERT_NO_THROW(menu.addItem(String("Uj vonat hozzadasa"), [&tarsasag]() {tarsasag.addVonat(); }));
		ASSERT_NO_THROW(menu.addItem(String("Vonatok kilistazasa"), [&tarsasag]() {tarsasag.listVonatok(); }));
		ASSERT_NO_THROW(menu.addItem(String("Teljesaru jegy vasarlasa"), [&tarsasag]() {tarsasag.buyTicket(); }));
		ASSERT_NO_THROW(menu.addItem(String("Diakjegy vasarlasa"), [&tarsasag]() {tarsasag.buyStudentTicket(); }));
		ASSERT_NO_THROW(menu.addItem(String("Eddig eladott jegyek"), [&tarsasag]() {tarsasag.eladottJegyek(); }));
		ASSERT_NO_THROW(menu.display());
	} END;

	TEST(0, tarsasag_ctor) {
		ASSERT_NO_THROW(Tarsasag t);
	} END
	Tarsasag tarsasag;
	TEST(1, uj_vonat) {
		tarsasag.addVonat();
		std::stringstream kiirt;
		tarsasag.listVonatok(kiirt);
		std::stringstream expected;
		expected << "Vonatok listaja:\n";
		expected << "Vonat | Indulasi allomas     | Vegallomas           | Indulasi ido | ";
		expected << "Erkezesi ido |   Alap ar | " << std::endl;

		expected << "1000  | Budapest             | Miskolc              | 12:00        | ";
		expected << "15:00        |      50Ft | " << std::endl;
		EXPECT_EQ(expected.str(), kiirt.str());
	} END;

	TEST(2, jegyek) {
		tarsasag.buyTicket();
		tarsasag.buyStudentTicket();
		std::stringstream kiirt;
		tarsasag.eladottJegyek(kiirt);
		std::stringstream expected;
		//1. menetjegy
		expected << "Jegyszam: " << 1000000 << std::endl;
		expected << "Menetjegy\n\t" << "Budapest" << " - " << "Miskolc" << "\n\t" << "12:00" << " - " << "15:00" << std::endl;
		expected << "Ar: " << 50 << "Ft" << std::endl;
		//2. helyjegy1
		expected << "Jegyszam: " << 1000001 << std::endl;
		expected << "Helyjegy\n\t" << "Budapest" << " - " << "Miskolc" << "\n\t" << "12:00" << " - " << "15:00" << std::endl;
		expected << "\tKocsi: " << 100 << " Hely: " << 1 << std::endl;
		expected << "Ar: " << 10 << "Ft" << std::endl;
		//3. diakjegy
		expected << "Jegyszam: " << 1000002 << std::endl;
		expected << "Diakjegy\n\t" << "Budapest" << " - " << "Miskolc" << "\n\t" << "12:00" << " - " << "15:00" << std::endl;
		expected << "\tDiakigazolvany szam: " << "71613347453" << std::endl;
		expected << "Ar: " << 5 << "Ft" << std::endl;
		//4. helyjegy2
		expected << "Jegyszam: " << 1000003 << std::endl;
		expected << "Helyjegy\n\t" << "Budapest" << " - " << "Miskolc" << "\n\t" << "12:00" << " - " << "15:00" << std::endl;
		expected << "\tKocsi: " << 100 << " Hely: " << 2 << std::endl;
		expected << "Ar: " << 10 << "Ft" << std::endl;
		EXPECT_EQ(expected.str(), kiirt.str());

	} END
	return 0;
}

int main() {
	
#if defined(CPORTA) 

	testMain();

#else //CPORTA
	
	releaseMain();

#endif //CPORTA

	return 0;
}