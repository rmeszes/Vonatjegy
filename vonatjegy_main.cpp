#include <iostream>
#include <cstdlib>
#include <Windows.h>

#include "gtest_lite.h"
#include "memtrace.h"

int main() {
	//A windowsban a megfelel� megjelen�t�shez
	#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
		SetConsoleCP(1250);
		SetConsoleOutputCP(1250);
	#endif
	std::cout << "\nA k�d lefutott, Enter a bez�r�shoz";
	std::cin.get();
	return 0;
}