#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <functional>

#include "memtrace.h"

#include "List.hpp"
#include "string.h"

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