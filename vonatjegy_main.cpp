#include <iostream>
#include <Windows.h>

#include "gtest_lite.h"
#include "memtrace.h"

#include "Vonat.h"
#include "List.h"
int main() {
	//A windowsban a megfelel� megjelen�t�shez
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
		EXPECT_EQ(1, list.getCurrent().getSzam());
	} ENDM

	std::cout << "\nA k�d lefutott, Enter a bez�r�shoz";
	std::cin.get();
	return 0;
}