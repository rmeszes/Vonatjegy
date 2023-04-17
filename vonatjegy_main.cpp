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

	TEST(create_list, create_list) {
		ASSERT_NO_THROW(List<Vonat> list);
	} ENDM

	TEST(list_add, list_add) {
		List<Vonat> list;
		Vonat vonat;
		ASSERT_NO_THROW(list.Add(vonat));
		EXPECT_EQ(0, list.getCurrent().getSzam());
	} ENDM

	TEST(list_next, list_next) {
		Vonat vonat1(1);
		Vonat vonat2(2);
		Vonat temp;
		List<Vonat> vonatok;
		vonatok.Add(vonat1);
		vonatok.Add(vonat2);
		int i = 1;
		while (vonatok.Next(temp) == true) {
			EXPECT_EQ(i++, temp.getSzam());
		}
	} ENDM

	std::cout << "\nA kód lefutott, Enter a bezáráshoz";
	std::cin.get();
	return 0;
}