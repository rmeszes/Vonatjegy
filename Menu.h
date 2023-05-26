#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <functional>

#include "memtrace.h"

#include "List.hpp"
#include "string.h"

using std::cout;
using std::cin;

/// <summary>
/// Egy szám bekérésére szolgál
/// </summary>
/// <param name="bekert_adat">A felhasználó számára kiírt üzenet, ami leírja mit kér a program</param>
/// <returns>Egy egész szám</returns>
size_t getnum(const char* bekert_adat, size_t max = SIZE_MAX, size_t min = 0);

/// <summary>
/// Egy osztály a konzolos menü kezelésére
/// </summary>
class Menu
{
	/// <summary>
	/// Egyetlen menüpontja a menünek. Valójában arra szolgál, hogy összekössön egy funckiót egy stringgel.
	/// </summary>
	struct MenuItem { // 2 elem összekötésére szolgál csak
		String label;
		std::function<void()> action;
	};

	List<MenuItem> menuItems;
public:
	//Hozzáad a menühöz egy elemet
	void addItem(const String& label, std::function<void()> action) {
		menuItems.push_back({ label,action });
	}

	//Megjeleníti a menüt a létrehozott elemekkel. +1 elem a kilépés
	void display();
};

#endif //MENU_HU