#include <iostream>
#include <Windows.h>

#include "gtest_lite.h"
#include "memtrace.h"

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
		EXPECT_EQ(1, lista[0]);
	} ENDM

	TEST(vonat, ctor) {
		Vonat v(1000, 1, 1);
		EXPECT_EQ(1000, v.getVonatSzam());
	} ENDM

	std::cout << "\nA kód lefutott, Enter a bezáráshoz";
	std::cin.get();
	return 0;
}