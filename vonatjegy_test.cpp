#include <iostream>
#include <Windows.h>

//#include "memtrace.h"
#include "gtest_lite.h"


#include "Vonat.h"
#include "List.hpp"

int main() {
	//A windowsban a megfelelõ megjelenítéshez
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);
#endif

	TEST(lista, ctor) {
		ASSERT_NO_THROW(List<size_t> lista);
	} ENDM

	TEST(list_add, hozzaadas) {
		List<size_t> lista;
		lista.Add(1);
		EXPECT_EQ(1, *lista[0]);
	} ENDM

	TEST(vonat, ctor) {
		ASSERT_NO_THROW(Vonat v(1000, 2, 3));
	} ENDM

	TEST(vonat_ertekek, getters) {
		Vonat v(1001, 4, 100);
		EXPECT_EQ(1001, v.getVonatSzam());
	} ENDM

	TEST(hely, foglalas) {
		Vonat v(1002, 3, 2);
		unsigned int hely[2];
		v.findSeat(hely);
		EXPECT_EQ(100, hely[0]);
		EXPECT_EQ(1, hely[1]);
	} ENDM

	List<Vonat> lista;
	lista.Add(Vonat(1000, 10, 60));

	std::cout << "\nA kód lefutott, Enter a bezáráshoz";
	std::cin.get();
	return 0;
}